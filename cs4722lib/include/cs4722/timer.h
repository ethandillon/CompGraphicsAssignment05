//
// Created by Ben on 7/12/2024.
//

#ifndef CS4722CODE_FA24_TIMER_H
#define CS4722CODE_FA24_TIMER_H

#include <iostream>
#include "GLFW/glfw3.h"

namespace cs4722 {

    class Timer {
    private:
        /**
         * \brief The last computed average weight
         */
        double _aRate = 0.0;
        /**
         * \brief The last time the step method was called
         */
        double _lastTime = 0.0;
        /**
         * \brief The last value of the time
         */
        double _time;
        /**
         * \brief The last value of the time-lapse between two calls to step.
         */
        double _delta;

    public:
        /**
         * \brief The weight given to the previous average rate when averaging with the
         * new instantaneous average.
         */
        double rateWeight = 100.0;

        /**
         * \brief Return the average rate last computed.
         */
        double aRate() const {
            return _aRate;
        }

        /**
         * \brief Return the instantaneous rate last computed.
         */
        double iRate() const {
            return 1 / _delta;
        }

        /**
         * \brief Return the time the step method was called last.
         */
        double time() const {
            return _time;
        }

        /**
         * \brief Return the time between the last two calls of the step method.
         */
        double deltaTime() const {
            return _delta;
        }

        /**
         * \brief Print out the average rate and the instantaneous rate to the console.
         */
        void printRates() const {
            std::cout << "average frame rate is " << aRate()
            << "   instantaneous frame rate " << iRate() << std::endl;
        }

        /**
         * \brief Compute time, delta, and the rates.
         */
        void step() {
            _time = glfwGetTime();
            _delta = _time - _lastTime;
            _lastTime = _time;
            _aRate = (rateWeight * _aRate + 1/_delta) / (rateWeight+1);
        }

    };


}


#endif //CS4722CODE_FA24_TIMER_H
