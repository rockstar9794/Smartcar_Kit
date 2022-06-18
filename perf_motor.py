from motor_details import MotorTools
import wiringpi


class Motor(MotorTools):

    IN1_PIN = 1
    IN2_PIN = 4
    IN3_PIN = 5
    IN4_PIN = 6
    TRIG_PIN = 28
    ECHO_PIN = 29
    MAX_SPEED = 50
    MIN_SPEED = 0
    OUTPUT = 1
    INPUT = 0
    SOFT_PWM_OUTPUT = 4

    def __init__(self):
        wiringpi.wiringPiSetup()
        pass

    def initUltrasonic(self):

        wiringpi.pinMode(self.TRIG_PIN, self.OUTPUT)
        wiringpi.pinMode(self.ECHO_PIN, self.INPUT)

    def initDCMotor(self):

        wiringpi.pinMode(self.IN1_PIN, self.SOFT_PWM_OUTPUT)
        wiringpi.pinMode(self.IN2_PIN, self.SOFT_PWM_OUTPUT)
        wiringpi.pinMode(self.IN3_PIN, self.SOFT_PWM_OUTPUT)
        wiringpi.pinMode(self.IN4_PIN, self.SOFT_PWM_OUTPUT)

        wiringpi.softPwmCreate(self.IN1_PIN, self.MIN_SPEED, self.MAX_SPEED)
        wiringpi.softPwmCreate(self.IN2_PIN, self.MIN_SPEED, self.MAX_SPEED)
        wiringpi.softPwmCreate(self.IN3_PIN, self.MIN_SPEED, self.MAX_SPEED)
        wiringpi.softPwmCreate(self.IN4_PIN, self.MIN_SPEED, self.MAX_SPEED)

    def goForward(self):

        wiringpi.softPwmWrite(self.IN1_PIN, self.MAX_SPEED)
        wiringpi.softPwmWrite(self.IN2_PIN, self.MIN_SPEED)
        wiringpi.softPwmWrite(self.IN3_PIN, self.MAX_SPEED)
        wiringpi.softPwmWrite(self.IN4_PIN, self.MIN_SPEED)

    def goForwardWithSpeed(self, speed):

        wiringpi.softPwmWrite(self.IN1_PIN, speed)
        wiringpi.softPwmWrite(self.IN2_PIN, self.MIN_SPEED)
        wiringpi.softPwmWrite(self.IN3_PIN, speed)
        wiringpi.softPwmWrite(self.IN4_PIN, self.MIN_SPEED)

    def goBackward(self):

        wiringpi.softPwmWrite(self.IN1_PIN, self.MIN_SPEED)
        wiringpi.softPwmWrite(self.IN2_PIN, self.MAX_SPEED)
        wiringpi.softPwmWrite(self.IN3_PIN, self.MIN_SPEED)
        wiringpi.softPwmWrite(self.IN4_PIN, self.MAX_SPEED)

    def goBackwardWithSpeed(self, speed):

        wiringpi.softPwmWrite(self.IN1_PIN, self.MIN_SPEED)
        wiringpi.softPwmWrite(self.IN2_PIN, speed)
        wiringpi.softPwmWrite(self.IN3_PIN, self.MIN_SPEED)
        wiringpi.softPwmWrite(self.IN4_PIN, speed)

    def goRight(self):

        wiringpi.softPwmWrite(self.IN1_PIN, self.MAX_SPEED)
        wiringpi.softPwmWrite(self.IN2_PIN, self.MIN_SPEED)
        wiringpi.softPwmWrite(self.IN3_PIN, self.MIN_SPEED)
        wiringpi.softPwmWrite(self.IN4_PIN, self.MAX_SPEED)

    def goLeft(self):

        wiringpi.softPwmWrite(self.IN1_PIN, self.MIN_SPEED)
        wiringpi.softPwmWrite(self.IN2_PIN, self.MAX_SPEED)
        wiringpi.softPwmWrite(self.IN3_PIN, self.MAX_SPEED)
        wiringpi.softPwmWrite(self.IN4_PIN, self.MIN_SPEED)

    def smoothLeft(self):

        wiringpi.softPwmWrite(self.IN1_PIN, self.MAX_SPEED/8)
        wiringpi.softPwmWrite(self.IN2_PIN, self.MIN_SPEED)
        wiringpi.softPwmWrite(self.IN3_PIN, self.MAX_SPEED)
        wiringpi.softPwmWrite(self.IN4_PIN, self.MIN_SPEED)

    def smoothRight(self):

        wiringpi.softPwmWrite(self.IN1_PIN, self.MAX_SPEED)
        wiringpi.softPwmWrite(self.IN2_PIN, self.MIN_SPEED)
        wiringpi.softPwmWrite(self.IN3_PIN, self.MAX_SPEED/8)
        wiringpi.softPwmWrite(self.IN4_PIN, self.MIN_SPEED)

    def stopDCMotor(self):

        wiringpi.softPwmStop(self.IN1_PIN)
        wiringpi.softPwmStop(self.IN2_PIN)
        wiringpi.softPwmStop(self.IN3_PIN)
        wiringpi.softPwmStop(self.IN4_PIN)

    def signalHandler(self, signal):
        self.stopDCMotor()
        exit(0)
