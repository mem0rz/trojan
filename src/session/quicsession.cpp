// quicsession.cpp
#include "quicsession.h"
#include <stdexcept>

QUICSession::QUICSession(SSL_CTX *ssl_ctx) {
    ssl_ = SSL_new(ssl_ctx);
    if (!ssl_) {
        throw std::runtime_error("Failed to create SSL object");
    }

    ngtcp2_conn_callbacks callbacks = {};
    ngtcp2_conn_settings settings;
    ngtcp2_settings_default(&settings);
    settings.initial_max_data = 1048576;

    if (ngtcp2_conn_server_new(&quic_conn_, nullptr, &settings, &callbacks, nullptr) != 0) {
        throw std::runtime_error("Failed to create QUIC connection");
    }
}

QUICSession::~QUICSession() {
    if (quic_conn_) {
        ngtcp2_conn_del(quic_conn_);
    }
    if (ssl_) {
        SSL_free(ssl_);
    }
}

void QUICSession::handle_packet(const uint8_t *data, size_t length) {
    ngtcp2_conn_read_pkt(quic_conn_, data, length, ngtcp2_timestamp_now());
}
