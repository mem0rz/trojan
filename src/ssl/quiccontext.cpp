// quiccontext.cpp
#include "quiccontext.h"
#include <stdexcept>

QUICContext::QUICContext(const std::string &cert_file, const std::string &key_file) {
    init_openssl(cert_file, key_file);
}

QUICContext::~QUICContext() {
    if (ssl_ctx_) {
        SSL_CTX_free(ssl_ctx_);
    }
}

void QUICContext::init_openssl(const std::string &cert_file, const std::string &key_file) {
    ssl_ctx_ = SSL_CTX_new(TLS_server_method());
    if (!ssl_ctx_) {
        throw std::runtime_error("Failed to create SSL context");
    }

    SSL_CTX_set_min_proto_version(ssl_ctx_, TLS1_3_VERSION);
    if (SSL_CTX_use_certificate_file(ssl_ctx_, cert_file.c_str(), SSL_FILETYPE_PEM) != 1 ||
        SSL_CTX_use_PrivateKey_file(ssl_ctx_, key_file.c_str(), SSL_FILETYPE_PEM) != 1) {
        throw std::runtime_error("Failed to load certificate or private key");
    }
}
