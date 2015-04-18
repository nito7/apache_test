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

typedef struct {
    char *message;
} rook_api_dir_config;

static void *rook_api_create_dir_config(apr_pool_t *p, char *path)
{
    rook_api_dir_config *cfg = (rook_api_dir_config *)apr_pcalloc(p, sizeof(rook_api_dir_config));
    cfg->message = (char *)"こんにちは！";
    return cfg;
}

static int rook_api_handler(request_rec *r)
{
    rook_api_dir_config *cfg = (rook_api_dir_config *) ap_get_module_config(r->per_dir_config, &rook_api_module);
    std::string messagetosend = std::string("<html><p>") + std::string(cfg->message) + std::string("</p><p>test</p></html>\n");
    r->content_type = "text/html";
    if (!r->header_only) {
      /*
      if (strcmp(r->handler, "rook_api") != 0) {
        std::cerr << "handler isn't rook_api" << std::endl;
        return OK;
      }
      */
      std::cerr << "return OK" << std::endl;
      ap_rputs(messagetosend.c_str(), r);
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
    rook_api_create_dir_config,
    NULL,
    NULL,
    NULL,
    NULL,
    register_hooks
  };
};

