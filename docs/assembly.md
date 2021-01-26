## Leg assembly

The robot uses 8 legs distributed in pairs. Each pair consists of a leg and its mirrored version. So in total, the robot requires a set of 4 legs and 4 mirrored legs.

The following table describes the parts required to assembe a single leg. These parts can be found under [parts/STL/leg](parts/STL/leg).

|Parts              | Quantity | 
|-------------------|----------|
| base-bone         |    1     |
| bone0             |    1     |
| bone1             |    1     |
| bone2             |    1     |
| bone3             |    1     |
| bone4             |    1     |
| bone5             |    1     |
| bone6             |    1     |
| bone7             |    1 	   |
| toe1              |    1 	   |
| toe2              |    1 	   |

To assemle a single mirrored leg, the files are the same, but have the suffix `_MIR`. These parts can be found under [parts/STL/leg_mirrored](parts/STL/leg_mirrored).

To assemble the different sections of each leg, you can use a piece of filament and a soldering iron (or a lighter) to melt the sides of the filament. You can see an example [here][1].

First, join base-bone with bone6 and bone7.

<img width=500px src="../images/assembly/leg1.PNG">
<img width=500px src="../images/assembly/leg2.PNG">

Then add bone1 and bone 2 to the other side of base-bone.

<img width=500px src="../images/assembly/leg3.PNG">
<img width=500px src="../images/assembly/leg4.PNG">

Then join bone4 with bone1 and proceed to attach bone3 to bone1 and bone2.

<img width=500px src="../images/assembly/leg5.PNG">
<img width=500px src="../images/assembly/leg6.PNG">

Next join bone4 and bone7 with bone5.

<img width=500px src="../images/assembly/leg7.PNG">
<img width=500px src="../images/assembly/leg8.PNG">

Now join bone5 and base-bone with bone0.

<img width=500px src="../images/assembly/leg9.PNG">
<img width=500px src="../images/assembly/leg10.PNG">

Finally, attach toe1 (the longer one) to bone4 and toe2 (the short one) to bone3.

<img width=500px src="../images/assembly/leg11.PNG">
<img width=500px src="../images/assembly/leg12.PNG">

## Body Assembly
For the body you need to print 3 parts, located under [parts/STL/body](parts/STL/body). You will also need 2 DC motors, 1 Servo and some bolts and nuts.
|Parts                       | Quantity | 
|----------------------------|----------|
| chasis                     |    1     |
| battery-holder             |    1     |
| battery-holder-robot       |    1     |
| M3x25 bolts                |    4     |
| M3 nuts                    |    4     |
| DC motors                  |    2     |
| Sg90 Servo                 |    1     |

First place the DC motors inside the chasis. You will notice that in the inside between them you can place 2 M3 nuts (can be optional if the bolts fit correctly on your print).
Then proceed to screw the M3x25 bolts to fasten the motors to the chasis.
Now you can put the battery-holder-robot part in the middle of the motors. Note that this part also has space for 2 M3 nuts. Proceed to fasten this part to the motors with the other 2 M3x25 bolts.
Then you can place the Servo with its shaft going through the chasis and fasten it with its set of screws (normally sold as misc with the servo).

<img width=500px src="../images/assembly/chasis1.PNG">
<img width=500px src="../images/assembly/chasis2.PNG">

Finally you can attach the battery-holder 3D printed part to your real 18650 battery holder (you can glue it or drill two M3 holes to the holder to fasten it to the printed part with 2 extra M3 bolts). Note that the battery-holder part slides inside the battery-holder-robot part. That way the robot can lift the batteries and at the same time they are easy to remove.

<img width=500px src="../images/assembly/chasis3.PNG">

## Full assembly
For the rest of the assembly you will need parts that can be found under [parts/STL/body](parts/STL/body) and [parts/STL/gears](parts/STL/gears).
You will need:

|Parts                            | Quantity | 
|---------------------------------|----------|
| assembled legs                  |    4     |
| assembled mirrored legs         |    4     |
| body assembled in previous step |    1     |
| big-gear                        |    4     |
| small-gear                      |    2     |
| gear-holder                     |    4     |
| gear1-shaft                     |    2     |
| gear2-shaft                     |    4     |

[1]: https://www.youtube.com/watch?v=RxB7USuMwRw&feature=youtu.be
