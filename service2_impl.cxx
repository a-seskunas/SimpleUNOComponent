/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 *  The Contents of this file are made available subject to the terms of
 *  the BSD license.
 *
 *  Copyright 2000, 2010 Oracle and/or its affiliates.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of Sun Microsystems, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *************************************************************************/

#include <cppuhelper/implbase3.hxx>
#include <cppuhelper/factory.hxx>
#include <cppuhelper/implementationentry.hxx>
#include <cppuhelper/supportsservice.hxx>
#include <uno/lbnames.h>
 
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XInitialization.hpp>
#include <com/sun/star/lang/IllegalArgumentException.hpp>
#include <inco/niocs/test/XSomething.hpp>
 
 
using namespace ::rtl; // for OUString
using namespace ::com::sun::star; // for sdk interfaces
using namespace ::com::sun::star::uno; // for basic types
 


namespace my_sc_impl {
    
    // service operations for MyService2Impl
    Sequence< OUString > getSupportedServiceNames_MyService2Impl()
    {
        Sequence<OUString> names(1);
        names[0] = OUString("inco.niocs.test.MyService2");
        return names;
    }
 
    OUString getImplementationName_MyService2Impl()
    {
        return OUString("inco.niocs.test.my_sc_impl.MyService2");
    }
 

    
 
    class MyService2Impl : public ::cppu::WeakImplHelper3< ::inco::niocs::test::XSomething, 
                                                           lang::XServiceInfo,
                                                           lang::XInitialization > 
    {
        OUString m_sArg;
        Reference<XComponentContext> m_xContext;
    public:

        inline MyService2Impl(Reference< XComponentContext > const & xContext) throw ()
            : m_xContext(xContext)
        {}
        virtual ~MyService2Impl() {}


        // no need to implement XInterface, XTypeProvider, XWeak

        // XServiceInfo methods
        virtual OUString SAL_CALL getImplementationName() throw( RuntimeException );
        virtual sal_Bool SAL_CALL supportsService( OUString const & serviceName ) throw (RuntimeException);
        virtual Sequence< OUString >  SAL_CALL getSupportedServiceNames() throw (RuntimeException);

        // XSomething methods
        virtual OUString SAL_CALL methodOne( OUString const & str ) throw (RuntimeException);
        virtual OUString SAL_CALL methodTwo() throw (RuntimeException);

        // XInitialization will be called upon
        // createInstanceWithArguments[AndContext]()
        virtual void SAL_CALL initialize( Sequence< Any > const & args ) throw (Exception);

    };

    // service operations from service1_impl.cxx
    extern Sequence< OUString > SAL_CALL getSupportedServiceNames_MyService1Impl();
    extern OUString SAL_CALL getImplementationName_MyService1Impl();
    extern Reference< XInterface > SAL_CALL create_MyService1Impl( Reference< XComponentContext > const & xContext );


    // XServiceInfo implementation
    OUString MyService2Impl::getImplementationName()
        throw (RuntimeException)
    {
        // unique implementation name
        return getImplementationName_MyService2Impl();
    }
    sal_Bool MyService2Impl::supportsService( OUString const & serviceName )
        throw (RuntimeException)
    {
        return cppu::supportsService(this, serviceName);
    }
    Sequence< OUString > MyService2Impl::getSupportedServiceNames()
        throw (RuntimeException)
    {
        return getSupportedServiceNames_MyService2Impl();
    }

    // XSomething implementation
    OUString MyService2Impl::methodOne( OUString const & str )
        throw (RuntimeException)
    {
        m_sArg = str;
        return OUString("called methodOne() of MyService2 implementation: ") + m_sArg;
    }

    OUString MyService2Impl::methodTwo()
        throw (RuntimeException)
    {
        return OUString("called methodTwo() of MyService2 implementation: ") + m_sArg;
    }


    // XInitialization implementation
    void MyService2Impl::initialize( Sequence< Any > const & args )
        throw (Exception)
    {
        if (args.getLength() != 1) {
            throw lang::IllegalArgumentException(
                                                 OUString("give a string instanciating this component!"),
                                                 // resolve to XInterface reference:
                                                 static_cast< ::cppu::OWeakObject * >(this),
                                                 0 ); // argument pos
        }
        if (! (args[ 0 ] >>= m_sArg)) {
            throw lang::IllegalArgumentException(
                                                 OUString("no string given as argument!"),
                                                 // resolve to XInterface reference:
                                                 static_cast< ::cppu::OWeakObject * >(this),
                                                 0 ); // argument pos
        }
    }




    Reference< XInterface > SAL_CALL create_MyService2Impl( Reference< XComponentContext > const & xContext )
    {
        return static_cast< lang::XTypeProvider * >( new MyService2Impl( xContext ) );
    }




    // This struct makes it easy to implement the extern "C" exported component operations
    // using helper functions.
    static struct ::cppu::ImplementationEntry s_component_entries [] =  
        {
            {   // Service1
                create_MyService1Impl, getImplementationName_MyService1Impl,
                getSupportedServiceNames_MyService1Impl, ::cppu::createSingleComponentFactory,
                0, 0  // last two entries reserved for future use, can be zeros.
            },
            {
                // Service2
                create_MyService2Impl, getImplementationName_MyService2Impl,
                getSupportedServiceNames_MyService2Impl, ::cppu::createSingleComponentFactory,
                0, 0
            },
            // NULL termination.
            { 0, 0, 0, 0, 0, 0 }
        };

}


// Exported component operations

extern "C" // To skip g++'s function name decorations
{

    SAL_DLLPUBLIC_EXPORT void * SAL_CALL component_getFactory(
			      sal_Char const * implName, lang::XMultiServiceFactory * xMgr,
			      registry::XRegistryKey * xRegistry )
    {
        return ::cppu::component_getFactoryHelper(
               implName, xMgr, xRegistry, ::my_sc_impl::s_component_entries );
    }

    SAL_DLLPUBLIC_EXPORT void SAL_CALL component_getImplementationEnvironment(
		              char const ** ppEnvTypeName, uno_Environment **)
    {
        *ppEnvTypeName = CPPU_CURRENT_LANGUAGE_BINDING_NAME;
    }

}
