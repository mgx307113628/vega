include platform.mk

SKYNET_PATH ?= ../skynet/skynet-src

CFLAGS = -g -O2 -Wall $(MYCFLAGS)
# CFLAGS += -DUSE_PTHREAD_LOCK


#CSERVICE_PATH ?= cservice
#CSERVICE = snlua logger gate harbor
#
#all : \
#  $(foreach v, $(CSERVICE), $(CSERVICE_PATH)/$(v).so) \
#
#$(CSERVICE_PATH) :
#	mkdir $(CSERVICE_PATH)
#
#define CSERVICE_TEMP
#  $$(CSERVICE_PATH)/$(1).so : service-src/service_$(1).c | $$(CSERVICE_PATH)
#	$$(CC) $$(CFLAGS) $$(SHARED) $$< -o $$@ -Iskynet-src
#endef
#
#$(foreach v, $(CSERVICE), $(eval $(call CSERVICE_TEMP,$(v))))
#
#clean :
#	rm -f $(CSERVICE_PATH)/*.so  && \
#  rm -rf $(CSERVICE_PATH)/*.dSYM



CSERVICE_PATH ?= cservice

all : $(CSERVICE_PATH)/mgx.so


$(CSERVICE_PATH)/mgx.so : test/service_mgx.c
	$(CC) $(CFLAGS) $(SHARED) $< -o $@ -I$(SKYNET_PATH)