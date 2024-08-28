#include "skynet.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

struct logger {
	FILE * handle;
	char * filename;
	uint32_t starttime;
	int close;
};

struct logger *
mgx_create(void) {
	printf("<mgx> Create Service\n");
	struct logger * inst = skynet_malloc(sizeof(*inst));
	inst->handle = NULL;
	inst->close = 0;
	inst->filename = NULL;

	return inst;
}

void
mgx_release(struct logger * inst) {
	printf("<mgx> Release Service\n");
	/*
	if (inst->close) {
		fclose(inst->handle);
	}
	skynet_free(inst->filename);
	*/
	skynet_free(inst);
}

#define SIZETIMEFMT	250

static int
timestring(struct logger *inst, char tmp[SIZETIMEFMT]) {
	uint64_t now = skynet_now();
	time_t ti = now/100 + inst->starttime;
	struct tm info;
	(void)localtime_r(&ti,&info);
	strftime(tmp, SIZETIMEFMT, "%d/%m/%y %H:%M:%S", &info);
	return now % 100;
}

static int
mgx_cb(struct skynet_context * context, void *ud, int type, int session, uint32_t source, const void * msg, size_t sz) {
	struct logger * inst = ud;
	switch (type) {
	case PTYPE_SYSTEM:
		break;
	case PTYPE_TEXT:
		/*
		if (inst->filename) {
			char tmp[SIZETIMEFMT];
			int csec = timestring(ud, tmp);
			fprintf(inst->handle, "%s.%02d ", tmp, csec);
		}
		fprintf(inst->handle, "[:%08x] ", source);
		fwrite(msg, sz , 1, inst->handle);
		fprintf(inst->handle, "\n");
		fflush(inst->handle);
		printf()
		*/
		char tmp[SIZETIMEFMT];
		int csec = timestring(ud, tmp);
		const char* cmsg = msg;
		printf("<mgx> %s.%02d [%s]\n", tmp, csec, cmsg);
		break;
	}

	return 0;
}

int
mgx_init(struct logger * inst, struct skynet_context *ctx, const char * parm) {
	printf("<mgx> Init Service\n");
	skynet_callback(ctx, inst, mgx_cb);
	return 0;
}

