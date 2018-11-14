# arduino-led-cluster

*A Massively Overengineered Arduino-Powered LED Matrix.*

This is a project page for a LED matrix design based around an attempt at 
pseudo-decentrelization where each light is controlled by its own Arduino 
and powered by its own battery. This design can be applied to something
other than LED lights, of course. 

The system is controlled by a master-slave configuration , yet each slave 
is responsible for its own logic, power and propagating the signal forward,
hence the term "pseudo-decentrilization".  

## Concept

```
*--------------* 
|              |     o--------o     o--------o             o--------o
|  CONTROLLER  | ==> |  UNIT  | ==> |  UNIT  | ==> ... ==> |  UNIT  |
|              |     o--------o     o--------o             o--------o
*--------------*
```

*Figure 1: A simplified diagram of how the components will connect with each other.*

Each **controller** is a Arduino Uno powered by 9v DC adapter connected to a wall outlet. It is responible for the following:
 - Sending out commands to its units

Each **unit** is a Arduino Nano and a RGB LED with appropriate resistors powered by a 9v battery. It is responsible for three things:
 - Recieve serial commands from the previous unit (or controller)
 - Parse the commands
 - Transmit the command to the next unit


### Commands and Macros
A command is a string sent over serial which follows the specification 
detailed below. These commands are sent from the **controller** and the 
**unit** then parses to determine what actions to execute. These 
commands are hardcoded in the **unit**, allowing us to strike a perfect
balance of complexity within the entire system since reduce the 
complexity of the commands by letting each **unit** have predetermined 
actions based on each command. 

These predetermined actions are known as **macros**. (or "actions" if we want to change it)

### Pros and Cons

The major pros of this design is twofold
 - Logic: The programming of each unit can be done in C, allowing us to create complex internal logic without having experience in integrated circuits. 
 - Power: We can avoid the issues that occur when supplying power to hundreds of LEDs from a central source, both in terms of voltage drop and wire gague. 

The cons:
 - Expensive: The fact that each light is controlled by an ATMEGA with their own 9V battery is not the cheapest way to achieve this effect.
 - One way comms: Each unit only listens one way and talks the other, so there is currently no way communicate the other way. 


## Showcase

//TODO: Add video of it in action!

## Design

### Components

#### LED id layout
| Column A | Column B | Column C | Column D | Column E | Column F | Column G | Column H | Column I | Column J |
| -------- | -------- | -------- | -------- | -------- | -------- | -------- | -------- | -------- | -------- |
| A01      | B01      | C01      | D01      | E01      | F01      | G01      | H01      | I01      | J01      |
| A02      | B02      | C02      | D02      | E02      | F02      | G02      | H02      | I02      | J02      |
| A03      | B03      | C03      | D03      | E03      | F03      | G03      | H03      | I03      | J03      |
| A04      | B04      | C04      | D04      | E04      | F04      | G04      | H04      | I04      | J04      |
| A05      | B05      | C05      | D05      | E05      | F05      | G05      | H05      | I05      | J05      |
| A06      | B06      | C06      | D06      | E06      | F06      | G06      | H06      | I06      | J06      |
| A07      | B07      | C07      | D07      | E07      | F07      | G07      | H07      | I07      | J07      |
| A08      | B08      | C08      | D08      | E08      | F08      | G08      | H08      | I08      | J08      |
| A09      | B09      | C09      | D09      | E09      | F09      | G09      | H09      | I09      | J09      |
| A10      | B10      | C10      | D10      | E10      | F10      | G10      | H10      | I10      | J10      |
| A11      | B11      | C11      | D11      | E11      | F11      | G11      | H11      | I11      | J11      |
| A12      | B12      | C12      | D12      | E12      | F12      | G12      | H12      | I12      | J12      |
| A13      | B13      | C13      | D13      | E13      | F13      | G13      | H13      | I13      | J13      |
| A14      | B14      | C14      | D14      | E14      | F14      | G14      | H14      | I14      | J14      |
| A15      | B15      | C15      | D15      | E15      | F15      | G15      | H15      | I15      | J15      |
| A16      | B16      | C16      | D16      | E16      | F16      | G16      | H16      | I16      | J16      |
| A17      | B17      | C17      | D17      | E17      | F17      | G17      | H17      | I17      | J17      |
| A18      | B18      | C18      | D18      | E18      | F18      | G18      | H18      | I18      | J18      |
| A19      | B19      | C19      | D19      | E19      | F19      | G19      | H19      | I19      | J19      |
| A20      | B20      | C20      | D20      | E20      | F20      | G20      | H20      | I20      | J20      |

#### Regex and Mathematical Equations

To indicate which arduinos should execute the command we use a combination of 
regex and mathematical equations. This allows us to with very few bytes select 
quite complicated groups of arduinos. 

The regex is read by the individual arduino and match their own id to the 
regex. If it matches, it means they are selected and they will execute the 
command. 

The mathematical equations are hard-coded boolean equations which will be told 
to run with certain parameters and if it equals the id of the arduino, it will 
be selected. These are a lot less flexible and are essentially included to 
allow for curves and circles without massive regexs.

**Example:**

> `/([ACEGI][\d][02468]|[BDFHJ][\d][13579])/` will select alternating lights in a checkers-style pattern.

>`/((E|F)\d{2}|\w(09|10))/` will select a two-pixel-line-width cross in the middle 

>`sin180` will use the column as a x value as degrees in a circle proportional to the number of columns with an offset of 180 degrees, matching lights in a sine wave. 
// TODO: not yet implemented

>`` will match blah

## Todo

 - [ ] Build prototype
 - [ ] Recreate in blender with python coding? To make lighting design easier

### Software

 - [ ] String parsing
    - [ ] Command
    - [ ] Identification
        - [ ] Regex-matching
        - [ ] Mathematical equation matching
    - [ ] Parameters
        - [ ] Read into list
    - [ ] Termination
    - [ ] Error handling
 - [ ] Mathematical equations
    - [ ] sin (cos, tan)
    - [ ] circle
    - [ ] equals
    - [ ] less than, greater than
 - [ ] Macros
    - [ ] Fade
        - [ ] Random fade
        - [ ] Gradient fade
        - [ ] Dimmer fade

### Hardware

#### Purchasing
 - [x] Order Arduinos
 - [ ] Recieve Arduinos
 - [x] Order LED lights
 - [ ] Recieve LED lights
 - [x] Order resistors
 - [ ] Recieve resistors
 - [x] Order wire
 - [ ] Recieve wire
 - [ ] Order 9v batteries
 - [ ] Recieve 9v batteries
 - [x] Order 9v battery connector
 - [ ] Recieve 9v battery connector

#### Assembly
 - [ ] Component diagram
 - [ ] Workshop-instructions for layman
 - [ ] Mark every single arduino