package com.example.akkaactormodel.classic

import org.springframework.stereotype.Service
import java.math.BigInteger
import java.util.*

@Service
class SingleThreadedPrimeGenerator {
    fun generatePrimeNumbers(count: Int): Set<BigInteger> = hashSetOf<BigInteger>().also { primes ->
        repeat(count) {
            val bigNumber = BigInteger(1500, Random())
            primes.add(bigNumber.nextProbablePrime())
            print(".")
        }
        println()
    }
}