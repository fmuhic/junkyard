package com.example.akkaactormodel.actor

import akka.actor.typed.ActorRef
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

    override fun createReceive(): Receive<String> =
        newReceiveBuilder()
            .onMessageEquals("say hello") {
                println("Hello!")
                return@onMessageEquals this
            }
            .onMessageEquals("who are you") {
                println("I am ${context.self.path()}")
                return@onMessageEquals this
            }
            .onMessageEquals("create child") {
                val secondActor: ActorRef<String> = context.spawn(SimpleBehavior.create(), "SecondActor")
                secondActor.tell("who are you")
                return@onMessageEquals this
            }
            .onAnyMessage {
                println("MessageReceived: $it")
                return@onAnyMessage this
            }
            .build()
}