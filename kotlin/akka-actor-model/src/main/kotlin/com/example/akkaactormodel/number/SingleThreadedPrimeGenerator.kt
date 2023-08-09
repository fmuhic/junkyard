package com.example.akkaactormodel.number

import org.springframework.stereotype.Service
import java.math.BigInteger
import java.util.*

@Service
class SingleThreadedPrimeGenerator {
    fun generatePrimeNumbers(count: Int): SortedSet<BigInteger> = TreeSet<BigInteger>().also { primes ->
        repeat(count) {
            val bigNumber = BigInteger(1200, Random())
            primes.add(bigNumber.nextProbablePrime())
            print(".")
        }
        println()
    }
}