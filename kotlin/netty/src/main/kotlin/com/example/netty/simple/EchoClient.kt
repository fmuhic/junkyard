package com.example.netty.simple

import io.github.oshai.kotlinlogging.KotlinLogging
import io.netty.bootstrap.Bootstrap
import io.netty.buffer.ByteBuf
import io.netty.buffer.Unpooled
import io.netty.channel.ChannelHandlerContext
import io.netty.channel.ChannelInboundHandlerAdapter
import io.netty.channel.ChannelInitializer
import io.netty.channel.nio.NioEventLoopGroup
import io.netty.channel.socket.SocketChannel
import io.netty.channel.socket.nio.NioSocketChannel
import org.springframework.stereotype.Service
import java.nio.charset.StandardCharsets


@Service
class EchoClient {

    companion object {
        private val log = KotlinLogging.logger { }
    }

    fun start() {
        val handler = EchoClientHandler()
        val group = NioEventLoopGroup()
        try {
            val bootstrap = Bootstrap()
                .group(group)
                .channel(NioSocketChannel::class.java)
                .handler(object : ChannelInitializer<SocketChannel>() {
                    override fun initChannel(ch: SocketChannel) {
                        ch.pipeline().addLast(handler)
                    }
                })
            val cf = bootstrap.connect("localhost", 8080).sync()
            cf.channel().closeFuture().sync()
        } catch (e: Exception) {
            log.error(e) { "Echo server error" }
        } finally {
            group.shutdownGracefully()
        }
    }
}

class EchoClientHandler : ChannelInboundHandlerAdapter() {
    companion object {
        private val log = KotlinLogging.logger { }
    }

    override fun channelActive(ctx: ChannelHandlerContext) {
        log.info { "Client sending message " }
        val message = Unpooled.copiedBuffer("Hello, Netty!", StandardCharsets.UTF_8)
        ctx.writeAndFlush(message)
    }

    override fun channelRead(ctx: ChannelHandlerContext, msg: Any) {
        val byteBuf = msg as ByteBuf
        log.info { "Client received from server: " + byteBuf.toString(StandardCharsets.UTF_8) }
        byteBuf.release()
    }

    override fun exceptionCaught(ctx: ChannelHandlerContext, cause: Throwable) {
        cause.printStackTrace()
        ctx.close()
    }
}