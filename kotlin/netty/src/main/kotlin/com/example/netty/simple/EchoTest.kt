package com.example.netty.simple

import org.springframework.boot.context.event.ApplicationReadyEvent
import org.springframework.context.event.EventListener
import org.springframework.stereotype.Service
import kotlin.concurrent.thread

@Service
class EchoTest(
    private val server: EchoServer,
    private val client: EchoClient,
) {
    @EventListener(ApplicationReadyEvent::class)
    fun run() {
        thread {
            server.start()
        }
        client.start()
    }
}