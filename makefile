ROOT=$(HOME)/extensions
LOROOT=$(HOME)/libreoffice
PRGROOT=$(HOME)/libreoffice/instdir/program
SDKBIN=$(HOME)/libreoffice/instdir/sdk/bin
OUT=SimpleUNOComponent.oxt

$(ROOT)/bin/$(OUT): $(ROOT)/lib/SimpleComponent.uno.so $(ROOT)/misc/SimpleComponent/SimpleComponent.rdb
	cp $(ROOT)/lib/SimpleComponent.uno.so $(ROOT)/misc/SimpleComponent/Linux_x86_64
	cd $(ROOT)/misc/SimpleComponent; zip -r $(ROOT)/bin/$(OUT) *

$(ROOT)/lib/SimpleComponent.uno.so: $(ROOT)/slo/SimpleComponent/service1_impl.o $(ROOT)/slo/SimpleComponent/service2_impl.o
	g++ -shared -Wl,-z,origin '-Wl,-rpath,' -L$(ROOT)/lib \
      		-L$(LOROOT)/instdir/sdk/lib -L$(LOROOT)/instdir/program \
      		-o $(ROOT)/lib/SimpleComponent.uno.so \
      		$(ROOT)/slo/SimpleComponent/service1_impl.o \
      		$(ROOT)/slo/SimpleComponent/service2_impl.o \
      		-luno_cppuhelpergcc3 -luno_cppu -luno_sal

$(ROOT)/slo/SimpleComponent/service2_impl.o: service2_impl.cxx
	gcc -c -fpic -fvisibility=hidden -O -I. -I$(ROOT)/inc \
      		-I$(ROOT)/inc/examples -I$(HOME)/libreoffice/instdir/sdk/include \
      		-I$(ROOT)/inc/SimpleComponent \
      		-DUNX -DGCC -DLINUX -DCPPU_ENV=gcc3 \
      		-o$(ROOT)/slo/SimpleComponent/service2_impl.o service2_impl.cxx


$(ROOT)/slo/SimpleComponent/service1_impl.o: service1_impl.cxx
	gcc -c -fpic -fvisibility=hidden -O -I. -I$(ROOT)/inc \
		-I$(ROOT)/inc/examples -I$(HOME)/libreoffice/instdir/sdk/include \
		-I$(ROOT)/inc/SimpleComponent \
		-DUNX -DGCC -DLINUX -DCPPU_ENV=gcc3 \
		-o$(ROOT)/slo/SimpleComponent/service1_impl.o service1_impl.cxx

$(ROOT)/misc/SimpleComponent/SimpleComponent.rdb: some.idl
	$(SDKBIN)/unoidl-write $(HOME)/libreoffice/udkapi some.idl $(ROOT)/misc/SimpleComponent/SimpleComponent.rdb
	$(SDKBIN)/cppumaker -Gc -O$(ROOT)/inc/SimpleComponent  \
                                    -Tinco.niocs.test.XSomething -Tinco.niocs.test.MyService1 -Tinco.niocs.test.MyService2 \
                                    $(ROOT)/misc/SimpleComponent/SimpleComponent.rdb \
                                    -X$(PRGROOT)/types.rdb -X$(PRGROOT)/types/offapi.rdb

#.PHONY: clean install
clean: 
	-rm $(ROOT)/bin/*
	#$(PRGROOT)/unopkg remove $(OUT)

install: 
	$(PRGROOT)/unopkg add $(ROOT)/bin/$(OUT)
