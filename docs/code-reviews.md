# Code Reviews

After each sprint, you'll be assigned one person to review  their code. You're required to do this three times in the semester. For each code review, you should reflect on and examine their code for clarity, best practice, potential errors, opportunities for improvement, optimisations and enhancements. You'll make comments and suggestiosn on their code and have a conversation with the person through GitHub about their code. This is an opportunity for you to become more familiar with and competent in reading and understanding code and an opportunity for you to help your classmates to write better code. 

## Why do code Reviews 

Developers strive to write great code without bugs. Unfortunately, just like with anything else, there’s no such thing as ideal software. Code review is a development process that was created specifically to address this problem. Instead of aiming at the impossible goal of writing perfect code and code without errors, with code reviews you can instead focus on catching problems early. Code reviews bring on a colleague (or a few) to give you more eyes on your work. Having code reviews as part of your development workflow brings a lot of benefits:

- __Fewer bugs.__ Developers can continue making errors as usual, but code reviews will decrease the amount of those bugs that make it into a final product.
- __Better security__. Code reviews make it easy to spot potential vulnerabilities and fix them before they make their way out the door. 
- __Knowledge sharing__. Members of your team can learn from each other by reviewing each other’s code.
- __Code quality__. Things like readability, efficiency, and maintainability of your code may not always directly affect your users but they are tremendously important in the long run of your project.
- __Better performance__. Code reviews help spot performance issues and ways to optimize or reduce redundancy and repetition in your code.

_Adapted from '[Code Review workflow](http://guides.beanstalkapp.com/code-review/guide-to-code-review.html)'_

## When and how a code review happens.

Code reviews will take place at the end of each Sprint...

1. __Pull Request + Merge:__ Each student will create a pull request to the main repo for their prototype code. This should include a) your Particle code, b) your wiring diagrams, c) supporting photos, diagrams, etc. and d) a link to an online video (youtube, vimeo) illustrating the current prototype. This will then all be merged into 

1. __Assignment:__ Once all the pull requests have been merged, you'll be randomly assigned one other person in the course to review. You'll have 1-2 days to complete the code review and you're expected to give as detailed feedback as possible i.e. help each other as much as possible.

1. __Comment:__ Review the code online and add comments to it. To do this, visit the [repo](https://github.com/daraghbyrne/advancediot2016) on GitHub, then select ['Commits'](https://github.com/daraghbyrne/advancediot2016/commits/master) and find the commit which relates to the person you've been assigned. Select it to view the code and then you can add a comment to the entire commit or to a specific line of code. 

See: [https://help.github.com/articles/commenting-on-differences-between-files/](https://help.github.com/articles/commenting-on-differences-between-files/)

__Don't forget__ We're using GitHub both because it's an awesome way to store and manage software but also because it makes it easy to share that code with others. Having shared access creates ease of access and visibility for everyone approach. Just because you're only assigned one person to review, doesn't mean you can't look at and learn from other people's code and/or add comments and give feedback to more people in the class. In fact, that would be very welcomed I'm sure!


## How to prepare for a code review?

It’s important to make sure that the people who will be reviewing your code have all the information they need to conduct the review:

- Make sure that your code is self-explanatory and has adequate amount of code documentation and comments.
- Make sure your variables and function are named well and self-explanatory
- Make sure your code is human readable - is it intended and nicely formatted? is it easy to see where functions begin and end? 
- Make sure each function begins with a detailed comment which explains what it's role is and why it does what it does.
- If you are fixing a bug in this update or think there might be a problem with the code that you can't solve,  include steps to reproduce the bug and any details that are necessary to verify the fix.
- When requesting a review, provide a short meaningful description of what this version implements/adds/changes.

_Also Adapted from '[Code Review workflow](http://guides.beanstalkapp.com/code-review/guide-to-code-review.html)'_

## Tips for Reviewing code

- Take a first look at the code. Can you quickly understand what is happening? Is this a sign that it isn't as clear as it needs to be?

- Take a look at complex code first. If there's more than 20-30 lines to do one thing, this is a good indicator that it needs to be broken up into a series of functions.

- See if you spot repetition of code or other ways to reduce the amount of code presented - is there pieces of code reused in other areas that could be aggregated into a function? 

- Look for better or more efficient ways to do the same thing - can a function be reduced or simplified into less lines of code? would a while be more efficient than a for loop? etc.

- During the review it’s better to submit many small comments and issues that are concise and actionable rather than a few very large comments that are hard to read and digest.

- Create a checklist of project-specific and programming language-specific things that you need to check during code reviews and use it for all reviews. The list can include things like checking if the code is documented appropriately, that it’s following your company’s code guidelines (or language’s general style guide), that features are covered with tests, that there is no code duplication, etc. It’s best to have that document available and used by the entire team.


### Guidance

A guide for reviewing code and having your code reviewed. Adapted from thoughtbot's [guides](https://github.com/thoughtbot/guides/tree/master/code-review)

##### Everyone

* Accept that many programming decisions are opinions. Discuss tradeoffs, which
  you prefer, and reach a resolution quickly.
* Ask questions; don't make demands. ("What do you think about naming this
  `someVariableName`?")
* Ask for clarification. ("I didn't understand this piece of the code. Can you clarify?")
* Avoid using terms that could be seen as referring to personal traits. ("dumb",
  "stupid"). Assume everyone is attractive, intelligent, and well-meaning.
* Be explicit. Remember people don't always understand your intentions online.
* Be humble. ("I'm not sure - let's look it up.")
* Don't use hyperbole. ("always", "never", "endlessly", "nothing")
* Talk in person if there are too many "I didn't understand" or "Alternative
  solution:" comments. Post a follow-up comment summarizing offline discussion.

##### Having Your Code Reviewed

* Be grateful for the reviewer's suggestions. ("Good call. I'll make that
  change.")
* Don't take it personally. The review is of the code, not you.
* Explain why the code exists. ("It's like that because of these reasons. Would
  it be more clear if I rename this class/file/method/variable?")
* Extract some changes and refactorings into future tickets/stories.
* Seek to understand the reviewer's perspective.
* Try to respond to every comment.

##### Reviewing Code

Understand why the change is necessary (fixes a bug, improves the user
experience, refactors the existing code). Then:

* Communicate which ideas you feel strongly about and those you don't.
* Identify ways to simplify the code while still solving the problem.
* If discussions turn too philosophical or academic, move the discussion offline. In the meantime, let the
  author make the final decision on alternative implementations.
* Offer alternative implementations, but assume the author already considered
  them. ("What do you think about using a this approach here?")
* Seek to understand the author's perspective.


## Read more:

1. [A Quick Guide for Code Reviews](https://www.lullabot.com/articles/a-quick-guide-for-code-reviews)
1. [Code Review: Why it matters](http://www.methodsandtools.com/archive/whycodereviews.php)
1. [A Guide to Code Inspections](http://www.ganssle.com/inspections.htm)
1. [Code review workflow](http://guides.beanstalkapp.com/code-review/guide-to-code-review.html)
1. [GitHub Guide - Commenting on differences between files](https://help.github.com/articles/commenting-on-differences-between-files/)

