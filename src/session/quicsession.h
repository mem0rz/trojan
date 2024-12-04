// quicsession.h
#ifndef _QUICSESSION_H_
#define _QUICSESSION_H_

#include <ngtcp2/ngtcp2.h>
#include <openssl/ssl.h>
#include <string>

class QUICSession {
public:
    QUICSession(SSL_CTX *ssl_ctx);
    ~QUICSession();

    void handle_packet(const uint8_t *data, size_t length);

private:
    ngtcp2_conn *quic_conn_;
    SSL *ssl_;
};

#endif // _QUICSESSION_H_
