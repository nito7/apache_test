#include "ap_config.h"
#include "apr.h"
#include "apr_lib.h"
#include "apr_strings.h"
#include "apr_network_io.h"
#include "apr_want.h"
#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_request.h"
#include "http_protocol.h"
#include <string.h>
#include <string>
#include <iostream>

extern "C" module AP_MODULE_DECLARE_DATA rook_api_module;

static int rook_api_handler(request_rec *r)
{
    if (strcmp(r->handler, "rook_api") != 0) {
      std::cerr << "handler isn't rook_api" << std::endl;
      return DECLINED;
    }

    r->content_type = "text/html";
    if (!r->header_only) {
      /* ここに処理を追加 */
      std::string message = "hello world";
      ap_rputs(message.c_str(), r);
    }
    return OK;
}

static void register_hooks(apr_pool_t *p)
{
  ap_hook_handler(rook_api_handler,NULL,NULL,APR_HOOK_MIDDLE);
}

extern "C" {
    module AP_MODULE_DECLARE_DATA rook_api_module = {
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    register_hooks
  };
};

