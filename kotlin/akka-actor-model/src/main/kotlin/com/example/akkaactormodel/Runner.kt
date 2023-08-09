package com.example.akkaactormodel

import com.example.akkaactormodel.number.MultiThreadedPrimeGenerator
import com.example.akkaactormodel.number.SingleThreadedPrimeGenerator
import org.springframework.boot.context.event.ApplicationReadyEvent
import org.springframework.context.event.EventListener
import org.springframework.stereotype.Service
import java.util.*

@Service
class Runner(
    private val singleThreadedPrimeGenerator: SingleThreadedPrimeGenerator,
    private val multiThreadedPrimeGenerator: MultiThreadedPrimeGenerator
) {
    @EventListener(ApplicationReadyEvent::class)
    fun start() {
        val start = System.currentTimeMillis()
        multiThreadedPrimeGenerator.generatePrimeNumbers(20)
        val duration = System.currentTimeMillis() - start
        println("Calculation took $duration ms")
    }
}