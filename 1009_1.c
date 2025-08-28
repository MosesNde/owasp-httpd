static int proxy_handler(request_rec *r)
{
    char *uri, *scheme, *p;
    if (!r->proxyreq || !r->filename || strncmp(r->filename, "proxy:", 6) != 0)
        return DECLINED;
    uri = r->filename + 6;
    p = strchr(uri, ':');
    if (p == NULL) {
        return HTTP_BAD_REQUEST;
    }
    scheme = apr_pstrndup(r->pool, uri, p - uri);
    if (strcasecmp(scheme, "http") != 0 && strcasecmp(scheme, "https") != 0) {
        return HTTP_BAD_REQUEST;
    }
    proxy_worker *worker = NULL;
    proxy_balancer *balancer = NULL;
    int access_status = proxy_run_scheme_handler(r, worker, NULL, uri, NULL, 0);
    return access_status;
}