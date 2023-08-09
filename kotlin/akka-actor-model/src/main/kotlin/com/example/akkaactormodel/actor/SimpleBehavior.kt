package com.example.akkaactormodel.actor

import akka.actor.typed.Behavior
import akka.actor.typed.javadsl.AbstractBehavior
import akka.actor.typed.javadsl.ActorContext
import akka.actor.typed.javadsl.Behaviors
import akka.actor.typed.javadsl.Receive

class SimpleBehavior private constructor(
    context: ActorContext<String>
) : AbstractBehavior<String>(context) {

    companion object {
        fun create(): Behavior<String> = Behaviors.setup(::SimpleBehavior)
    }
    override fun createReceive(): Receive<String> {
        return newReceiveBuilder()
            .onAnyMessage {
                println("MessageReceived $it")
                return@onAnyMessage this
            }
            .build()
    }
}