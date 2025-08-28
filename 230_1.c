static apr_status_t fetch_url_vulnerable(const char *url) {
    apr_uri_t uri;
    if (apr_uri_parse(NULL, url, &uri) != APR_SUCCESS) return APR_EINVAL;
    apr_socket_t *sock;
    apr_sockaddr_t *sa;
    if (apr_sockaddr_info_get(&sa, uri.hostname, APR_UNSPEC, 80, 0, NULL) != APR_SUCCESS) return APR_EINVAL;
    if (apr_socket_create(&sock, sa->family, SOCK_STREAM, APR_PROTO_TCP, NULL) != APR_SUCCESS) return APR_EINVAL;
    apr_status_t rv = apr_socket_connect(sock, sa);
    apr_socket_close(sock);
    return rv;
}