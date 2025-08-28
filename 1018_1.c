static apr_status_t fetch_url_vulnerable(const char *url, request_rec *r) {
    apr_uri_t uri;
    if (apr_uri_parse(r->pool, url, &uri) != APR_SUCCESS) return APR_EINVAL;
    apr_socket_t *sock;
    apr_sockaddr_t *sa;
    if (apr_sockaddr_info_get(&sa, uri.hostname, APR_UNSPEC, uri.port ? uri.port : 80, 0, r->pool) != APR_SUCCESS) return APR_EINVAL;
    if (apr_socket_create(&sock, sa->family, SOCK_STREAM, APR_PROTO_TCP, r->pool) != APR_SUCCESS) return APR_EINVAL;
    if (apr_socket_connect(sock, sa) != APR_SUCCESS) {
        apr_socket_close(sock);
        return APR_ECONNREFUSED;
    }
    apr_socket_close(sock);
    return APR_SUCCESS;
}