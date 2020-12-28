#include "util.h"

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

int net_init(char* netarg)
{
    UNUSED(netarg);
    return -1;
}
int net_send(void* req, int reqlen)
{
    printf("SEND %d\n", reqlen);

#ifdef EMSCRIPTEN
    return EM_ASM_INT({
        return window["netSend"]($0, $1);
    }, req, reqlen);
#else
    UNUSED(req);
    UNUSED(reqlen);
    return -1;
#endif


}


void net_poll(void (*cb)(void* data, int len))
{
#ifdef EMSCRIPTEN
    EM_ASM_({
      window["netPollSet"]($0);
    }, cb);
#else
    UNUSED(cb);
#endif
}

