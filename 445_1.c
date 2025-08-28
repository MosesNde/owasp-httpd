int fetch_url(request_rec *r, const char *url) {
    ap_rprintf(r, "Fetching URL: %s", url);
    
    return 0;
}