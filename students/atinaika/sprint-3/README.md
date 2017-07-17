# Sprint 3: Connectivity

### Sprint Catalog
At the beginning of the sprint, the mat could primarily do 3 things:
1. Allow the user to set a timer (input through a touch pot and indicated using an LED strip)
2. Play meditation music from a playlist
3. Provide soothing meditative feedback when touched at certain points

However during Sprint 3, I took a detour from my original concept to explore different methods to add connectivity to my yoga mat. I explored 2 primary concepts:
1. Connected yoga mats for partners or student-teacher pairs (viz. when one user opens a mat, an indication goes out to the other person regarding a joint meditation session)
2. Indicative yoga mat (viz. when a user is meditating during practise a notifier to goes to their close kins to not disturb them)

### Sprint Review  

While I didn't make progress on previously built features, I was able to send and receive a Particle event when the mat was opened. This would in the future be used to send an ambient or explicit notification to either another mat or to people.

This sprint was more about exploration where I questioned my concept a lot. As mentioned previously I begun to take detours trying to figure what to excite the user and would offer a great value proposition.

### End of Sprint Prototype

Below is a demo of the working feature. In short, I've used copper wires at the bottom and top-edge of the mat. When the mat is closed, the copper wires come into contact completing a circuit and triggering an event.

An event is triggered when the mat is closed (indicated by the red light blinking) and when the mat is opened (indicated by the green light and neo-pixel ring blinking.)

<!-- ![[]("https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint3/students/atinaika/files/sprint3/OpeningClosingThumbnail.png")]("https://www.youtube.com/embed/jsdSVK2a4Co?autoplay=1") -->

https://www.youtube.com/embed/jsdSVK2a4Co

<!-- <embed width="420" height="315" src="https://www.youtube.com/embed/jsdSVK2a4Co?autoplay=1"></embed> -->

Additionally I built a stand for the mat (image below), which could be used as a wireless charging station so that users don't have to seperately charge it.

<img src="https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint3/students/atinaika/files/sprint3/MatStand.jpg" height=600>

### Sprint Retrospective

Personally, I felt I could have been more decisive with the features. The technical implementation was not as challenging as was the decision of distinguishing features to be added.

It was however interesting working on the idea of the opening and closing of the mat triggering an event.

<b>User Testing</b>
At the completion of the sprint, I tested with 2 users who perform yoga regularly.

<img src="https://github.com/daraghbyrne/advancediot2017/blob/advait-sprint3/students/atinaika/files/sprint3/UserTesting/UserTestingCollage.jpg" height=600>

Feedback I received:
1. "I'd be great if no one disturbs me during meditation. I keep getting calls from people and when I don't respond they get concerned. A DND feature would be nice."
2. "I prefer to do my practise by myself and through Youtube videos, I may not want to the mat connected to someone else's mat."
3. "I don't have the time or money to go to classes. Teachers are really expensive here. A mat like this might be useful if I can listen to someone's instructions."
4. "A great addition would be to provide suggestions on youtube videos to watch or recitations to listen to."

### Next

Based on the user testing feedback,
1. I've decided to can the idea of connected mats
2. Will add a do not disturb feature, which either mutes the phone, or sends out an SMS to close relatives / friends to not disturb the person during practise
