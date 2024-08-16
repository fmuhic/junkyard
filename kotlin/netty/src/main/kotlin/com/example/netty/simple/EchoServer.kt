package com.example.netty.simple

import io.github.oshai.kotlinlogging.KotlinLogging
import io.netty.bootstrap.ServerBootstrap
import io.netty.buffer.ByteBuf
import io.netty.buffer.Unpooled
import io.netty.channel.*
import io.netty.channel.ChannelHandler.Sharable
import io.netty.channel.nio.NioEventLoopGroup
import io.netty.channel.socket.SocketChannel
import io.netty.channel.socket.nio.NioServerSocketChannel
import io.netty.util.CharsetUtil
import org.springframework.boot.context.event.ApplicationReadyEvent
import org.springframework.context.event.EventListener
import org.springframework.stereotype.Service
import java.net.InetSocketAddress


@Service
class EchoServer {

    companion object {
        private val log = KotlinLogging.logger {}
        private const val PORT = 8080
    }

    fun start() {
        val handler = EchoServerHandler()
        val bossGroup: EventLoopGroup = NioEventLoopGroup()
        val workerGroup: EventLoopGroup = NioEventLoopGroup()
        try {
            val bootstrap = ServerBootstrap()
            bootstrap.group(bossGroup, workerGroup)
                .channel(NioServerSocketChannel::class.java)
                .childHandler(object : ChannelInitializer<SocketChannel>() {
                    @Throws(java.lang.Exception::class)
                    public override fun initChannel(ch: SocketChannel) {
                        ch.pipeline().addLast(handler)
                    }
                })
            log.info { "Starting server at port $PORT" }
            val cf: ChannelFuture =  bootstrap.bind(InetSocketAddress(PORT)).sync()
            cf.channel().closeFuture().sync()
        } catch (e: Exception) {
            log.error(e) { "Echo server error" }
        } finally {
            workerGroup.shutdownGracefully()
            bossGroup.shutdownGracefully()
        }
    }
}

@Sharable
class EchoServerHandler: ChannelInboundHandlerAdapter() {

    companion object {
        private val log = KotlinLogging.logger {}
    }

    override fun channelRead(ctx: ChannelHandlerContext, msg: Any) {
        val input = msg as ByteBuf
        log.info { "Echo server received: ${input.toString(CharsetUtil.UTF_8)}" }
        ctx.write(msg)
    }

    override fun channelReadComplete(ctx: ChannelHandlerContext) {
        ctx.writeAndFlush(Unpooled.EMPTY_BUFFER)
            .addListener(ChannelFutureListener.CLOSE)
    }

    @Deprecated("Deprecated in Java")
    override fun exceptionCaught(ctx: ChannelHandlerContext, cause: Throwable) {
        cause.printStackTrace()
        ctx.close()
    }
}