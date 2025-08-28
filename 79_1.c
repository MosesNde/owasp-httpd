int fetch_url_content(const char *url, char *buffer, size_t buffer_size) {
    FILE *fp = popen((const char *)url, "r");
    if (!fp) return -1;
    size_t total_read = 0;
    while (fgets(buffer + total_read, buffer_size - total_read, fp) != NULL) {
        total_read = strlen(buffer);
        if (total_read >= buffer_size - 1) break;
    }
    pclose(fp);
    return 0;
}