// quiccontext.h
#ifndef _QUICCONTEXT_H_
#define _QUICCONTEXT_H_

#include <ngtcp2/ngtcp2.h>
#include <ngtcp2/ngtcp2_crypto.h>
#include <openssl/ssl.h>
#include <string>

class QUICContext {
public:
    QUICContext(const std::string &cert_file, const std::string &key_file);
    ~QUICContext();

    SSL_CTX *get_ssl_ctx() const { return ssl_ctx_; }

private:
    SSL_CTX *ssl_ctx_;
    void init_openssl(const std::string &cert_file, const std::string &key_file);
};

#endif // _QUICCONTEXT_H_
