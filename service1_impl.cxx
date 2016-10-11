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

#include <cppuhelper/implbase2.hxx>
#include <cppuhelper/factory.hxx>
#include <cppuhelper/supportsservice.hxx>
 
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XInitialization.hpp>
#include <inco/niocs/test/XSomething.hpp>
 
 
using namespace ::rtl; // for OUString
using namespace ::com::sun::star; // for sdk interfaces
using namespace ::com::sun::star::uno; // for basic types
 
 
namespace my_sc_impl {

    // service operations for MyService1Impl
    Sequence< OUString > getSupportedServiceNames_MyService1Impl()
    {
        Sequence<OUString> names(1);
        names[0] = OUString("inco.niocs.test.MyService1");
        return names;
    }

    OUString getImplementationName_MyService1Impl()
    {
        return OUString("inco.niocs.test.my_sc_impl.MyService1");
    }


    
 
    class MyService1Impl : public ::cppu::WeakImplHelper2< ::inco::niocs::test::XSomething, 
                                                           lang::XServiceInfo > 
    {
	
    public:
	
        // XServiceInfo methods
        virtual OUString SAL_CALL getImplementationName() throw( RuntimeException );
        virtual sal_Bool SAL_CALL supportsService( OUString const & serviceName ) throw (RuntimeException);
        virtual Sequence< OUString >  SAL_CALL getSupportedServiceNames() throw (RuntimeException);

        // XSomething methods
        virtual OUString SAL_CALL methodOne( OUString const & str ) throw (RuntimeException);
        virtual OUString SAL_CALL methodTwo() throw (RuntimeException);

    };

    // XServiceInfo implementation
    OUString MyService1Impl::getImplementationName()
        throw (RuntimeException)
    {
        // unique implementation name
        return getImplementationName_MyService1Impl();
    }
    sal_Bool MyService1Impl::supportsService( OUString const & serviceName )
        throw (RuntimeException)
    {
        return cppu::supportsService(this, serviceName);
    }
    Sequence< OUString > MyService1Impl::getSupportedServiceNames()
        throw (RuntimeException)
    {
        return getSupportedServiceNames_MyService1Impl();
    }

    // XSomething implementation
    OUString MyService1Impl::methodOne( OUString const & str )
        throw (RuntimeException)
    {
        return OUString("called methodOne() of MyService1 implementation: ") + str;
    }

    OUString MyService1Impl::methodTwo()
        throw (RuntimeException)
    {
        return OUString("called methodTwo() of MyService1 implementation: ");
    }




    Reference< XInterface > SAL_CALL create_MyService1Impl( Reference< XComponentContext > const & xContext )
    {
        return static_cast< lang::XTypeProvider * >( new MyService1Impl() );
    }


}
