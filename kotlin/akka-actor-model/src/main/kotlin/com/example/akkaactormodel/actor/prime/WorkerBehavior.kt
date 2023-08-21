package com.example.akkaactormodel.actor.prime

import akka.actor.typed.ActorRef
import akka.actor.typed.Behavior
import akka.actor.typed.javadsl.AbstractBehavior
import akka.actor.typed.javadsl.ActorContext
import akka.actor.typed.javadsl.Behaviors
import akka.actor.typed.javadsl.Receive
import com.example.akkaactormodel.actor.prime.ManagerCommand
import com.example.akkaactormodel.actor.prime.ResultManagerCommand
import java.io.Serializable
import java.math.BigInteger
import java.util.*

class WorkerBehavior private constructor(
    private val context: ActorContext<WorkerCommand>
): AbstractBehavior<WorkerCommand>(context) {

    companion object {
        fun create(): Behavior<WorkerCommand> = Behaviors.setup(::WorkerBehavior)
    }
    override fun createReceive(): Receive<WorkerCommand> =
        newReceiveBuilder()
            .onAnyMessage { command ->
                if (command.msg == "start") {
                    val id = context.self.path()
                    //println("Worker $id started ...")
                    val bigNumber = BigInteger(1500, Random())
                    val nextPrime = bigNumber.nextProbablePrime()
                    //println("Worker $id: Next probable prime is ${bigNumber.nextProbablePrime()}")
                    command.sender.tell(ResultManagerCommand(nextPrime))
                }
                return@onAnyMessage this
            }
            .build()
}

class WorkerCommand (
    private val actorMsg: String,
    private val actorSender: ActorRef<ManagerCommand>
): Serializable {
    val msg get() = actorMsg
    val sender get() = actorSender
}
