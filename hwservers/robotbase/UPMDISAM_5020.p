;SectionFlags for : 
;  Robot parameter file

Section General settings
;SectionFlags for General settings: 
Class Pioneer            ; general type of robot
Subclass patrolbot-sh    ; specific type of robot
RobotRadius 250          ; radius in mm
RobotDiagonal 120        ; half-height to diagonal of octagon
RobotWidth 425           ; width in mm
RobotLength 510          ; length in mm of the whole robot
RobotLengthFront 255     ; length in mm to the front of the robot (if this is 0
                         ; (or non existant) this value will be set to half of
                         ; RobotLength)
RobotLengthRear 255      ; length in mm to the rear of the robot (if this is 0
                         ; (or non existant) this value will be set to half of
                         ; RobotLength)
Holonomic true           ; turns in own radius
MaxRVelocity 500         ; absolute maximum degrees / sec
MaxVelocity 2200         ; absolute maximum mm / sec
MaxLatVelocity 0         ; absolute lateral maximum mm / sec
HasMoveCommand true      ; has built in move command
RequestIOPackets true    ; automatically request IO packets
RequestEncoderPackets false ; automatically request encoder packets
SwitchToBaudRate 38400   ; switch to this baud if non-0 and supported on robot

Section Conversion factors
;SectionFlags for Conversion factors: 
AngleConvFactor 0.001534 ; radians per angular unit (2PI/4096)
DistConvFactor 1         ; multiplier to mm from robot units
VelConvFactor 1          ; multiplier to mm/sec from robot units
RangeConvFactor 1        ; multiplier to mm from sonar units
DiffConvFactor 0.0056    ; ratio of angular velocity to wheel velocity (unused
                         ; in newer firmware that calculates and returns this)
Vel2Divisor 20           ; divisor for VEL2 commands
GyroScaler 1.626         ; Scaling factor for gyro readings

Section Accessories the robot has
;SectionFlags for Accessories the robot has: 
TableSensingIR false     ; if robot has upwards facing table sensing IR
NewTableSensingIR false  ; if table sensing IR are sent in IO packet
FrontBumpers true        ; if robot has a front bump ring
NumFrontBumpers 6        ; number of front bumpers on the robot
RearBumpers true         ; if the robot has a rear bump ring
NumRearBumpers 6         ; number of rear bumpers on the robot

Section Sonar parameters
;SectionFlags for Sonar parameters: 
SonarNum 16              ; number of sonar on the robot
;  SonarUnit <sonarNumber> <x position, mm> <y position, mm> <heading of disc,
;  degrees>
SonarUnit 0 83 229 90
SonarUnit 1 169 202 55
SonarUnit 2 232 134 30
SonarUnit 3 263 46 10
SonarUnit 4 263 -46 -10
SonarUnit 5 232 -134 -30
SonarUnit 6 169 -202 -55
SonarUnit 7 83 -229 -90
SonarUnit 8 -83 -229 -90
SonarUnit 9 -169 -202 -125
SonarUnit 10 -232 -134 -150
SonarUnit 11 -263 -46 -170
SonarUnit 12 -263 46 170
SonarUnit 13 -232 134 150
SonarUnit 14 -169 202 125
SonarUnit 15 -83 229 90

Section IR parameters
;SectionFlags for IR parameters: 
IRNum 0                  ; number of IRs on the robot
;  IRUnit <IR Number> <IR Type> <Persistance, cycles> <x position, mm> <y
;  position, mm>

Section Movement control parameters
;  if these are 0 the parameters from robot flash will be used, otherwise these
;  values will be used
;SectionFlags for Movement control parameters: 
SettableVelMaxes true    ; if TransVelMax and RotVelMax can be set
TransVelMax 0            ; maximum desired translational velocity for the robot
RotVelMax 0              ; maximum desired rotational velocity for the robot
SettableAccsDecs true    ; if the accel and decel parameters can be set
TransAccel 0             ; translational acceleration
TransDecel 0             ; translational deceleration
RotAccel 0               ; rotational acceleration
RotDecel 0               ; rotational deceleration
HasLatVel false          ; if the robot has lateral velocity
LatVelMax 0              ; maximum desired lateral velocity for the robot
LatAccel 0               ; lateral acceleration
LatDecel 0               ; lateral deceleration


Section Laser parameters
;SectionFlags for Laser parameters: 
LaserType lms2xx         ; type of laser
LaserPortType serial     ; type of port the laser is on
LaserPort /dev/ttyS2           ; port the laser is on
LaserAutoConnect false   ; if the laser connector should autoconnect this 
laser
                         ; or not
LaserFlipped true        ; if the laser is upside-down or not
LaserPowerControlled false ; if the power to the laser is controlled by serial
LaserMaxRange 0          ; Max range to use for the laser, 0 to use default
                         ; (only use if you want to shorten it from the
                         ; default), mm
LaserCumulativeBufferSize 0 ; Cumulative buffer size to use for the laser, 0 to
                         ; use default
LaserX 37                ; x location of laser, mm
LaserY 0                 ; y location of laser, mm
LaserTh 0                ; rotation of laser, deg
LaserZ 0                 ; height of the laser off the ground, mm (0 means
                         ; unknown)
LaserIgnore -76--72 72-76 ; Readings within a degree of the listed degrees
                         ; (separated by a space) will be ignored
LaserStartDegrees        ; start degrees for the sensor (leave blank for
                         ; default, use this to constrain the range) (double)
LaserEndDegrees          ; start degrees for the sensor (leave blank for
                         ; default, use this to constrain the range) (double)
LaserDegreesChoice       ; degrees choice for the sensor (leave blank for
                         ; default, use this to constrain the range)
LaserIncrement		    ; Increment for the sensor (leave blank for default,
                         ; use this to have a custom increment) (double)
LaserIncrementChoice     ; Increment for the sensor (leave blank for default,
                         ; use this to have a larger increment)
LaserUnitsChoice	     ; Units for the sensor (leave blank for default, use
                         ; this to have a larger units)
LaserReflectorBitsChoice  ; ReflectorBits for the sensor (leave blank for
                         ; default, use this to have a larger units)
LaserStartingBaudChoice  ; StartingBaud for the sensor (leave blank for
                         ; default, use this to have a larger StartingBaud)
LaserAutoBaudChoice      ; AutoBaud for the sensor (leave blank for default,
                         ; use this to have a larger units)