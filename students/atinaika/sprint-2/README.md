# Sprint 2: Adding Intelligence

### Sprint Catalog

|Features|Status|
|--------|------|
|LED strip indicator|Completed|
|Input for setting time|Completed|
|Switching between modes:<br><p>Yoga and meditation</p>|Completed|
|Audio tracks for meditation and yoga|Compeleted|
|Soothing tactile vibration during practise|Completed|
|Tactile notification|Completed|
|Opening & closing interaction|Outstanding|
|Convenient powering mechanism|Outstanding|
|Providing data from mat to phone|Outstanding|
|Build the form|Outstanding|

### Sprint Review

During this sprint, I set out to refine the features that I'd built in the first sprint. The focus was to make the interactions more intuitive and the feedback more natural and calming. I added subtle points like having a wave-like vibration pattern, akin to one's breath, and vibration only upon touching the surface.
While I tried to work with a pulse sensor I realised that there was a lot of noise in the readings. Also I reconsidered the utilitiy of the sensor and realised that it wouldn't be a significant value add.

### End of Sprint Prototype
![alt text](https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint2/students/atinaika/files/sprint2/closeUp-sprint2.jpg)

### Sprint Retrospective

Sprint 2 was more about a couple of main challenges
1. Optimizing code (Previously the code was linear and not stateful. This led to the timer for the practise stopping the entire code.)
2. Providing soothing tactile feedback (academically, a deep breath lasts 10 secs where the exhalation time is twice the inhalation time. Getting this into a sine pattern proved slightly challenging)
3. Working with heart rate monitor. (This was continuously giving me erroneous values despite correct connections)

Most of the other technical challenges (touch-based vibration, changing modes between yoga and meditation, improving sound fidelity) were accomplished without a hassle.

### Next
Next steps (in priority order):
1. Develop the opening and closing mechanism
2. Improve sound fidelity, possibly using 2 speakers
3. Add connectivity to mat
4. Integrate circuitry and components into the form of the mat
5. Powering the mat
6. Add appropriate tunes for yoga and meditation

