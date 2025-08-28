AP_DECLARE(apr_status_t) vulnerable_fetch_url_content(const char *url, char **response, apr_size_t *response_len, request_rec *r) {
    apr_socket_t *sock;
    apr_sockaddr_t *sa;
    apr_status_t rv = apr_sockaddr_info_get(&sa, url, APR_UNSPEC, 80, 0, r->pool);
    if (rv != APR_SUCCESS) {
        return rv;
    }
    if (apr_socket_create(&sock, sa->family, SOCK_STREAM, APR_PROTO_TCP, r->pool) != APR_SUCCESS) {
        return APR_EGENERAL;
    }
    if (apr_socket_connect(sock, sa) != APR_SUCCESS) {
        apr_socket_close(sock);
        return APR_EGENERAL;
    }
    char buffer[8192];
    apr_size_t len = 0;
    apr_size_t total_len = 0;
    *response = apr_palloc(r->pool, 8192);
    if (!*response) {
        apr_socket_close(sock);
        return APR_ENOMEM;
    }
    while ((rv = apr_socket_recv(sock, buffer, &(len = sizeof(buffer)))) == APR_SUCCESS && len > 0) {
        if (total_len + len > 8191) {
            break;
        }
        memcpy(*response + total_len, buffer, len);
        total_len += len;
    }
    (*response)[total_len] = '\0';
    *response_len = total_len;
    apr_socket_close(sock);
    return APR_SUCCESS;
}