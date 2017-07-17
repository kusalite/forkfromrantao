# Project Spec

A project specification is a guide for a sprint. It contains the details of the features and things you want to add to your product. 

## Functional Specifications

> A functional specification describes how a product will work entirely from the user's perspective. It doesn't care how the thing is implemented. It talks about features. It specifies screens, menus, dialogs, and so on.
> Taken from [Painless Functional Specifications](http://www.joelonsoftware.com/articles/fog0000000035.html)

The main goal of a functional specification is to describe the features that your IoT device will implement and the importance. The specification builds a wishlist of behaviors, functions and operations that your device will incorporate and these become what's known as a 'product backlog', a set of features remaining to be implemented. It's best to start with the core things that you can't do without and then make wishlists of nice to haves, bonus features and other bells and whistles that will make it a better product. 

A functional specification could also be called a 'requirments document', a 'design document', 'use cases' or 'user stories'. It's goal is to define the requirements to be implemented and the externally visible behavior of the software/hardware. It is 'the result of the synthesis of those needs into a coherent view of what the system will actually be.' 

> Writing a spec is a great way to nail down all those irritating design decisions, large and small, that get covered up if you don't have a spec. Even small decisions can get nailed down with a spec. For example, if you're building a web site with membership, you might all agree that if the user forgets their password, you'll mail it to them. Great. But that's not enough to write the code. To write the code, you need to know the actual words in that email. At most companies, programmers aren't trusted with words that a user might actually see (and for good reason, much of the time). So a marketing person or a PR person or some other English major is likely to be required to come up with the precise wording of the message. "Dear Shlub, Here's the password you forgot. Try not to be so careless in the future." When you force yourself to write a good, complete spec (and I'll talk a lot more about that soon), you notice all these things and you either fix them or at least you mark them with a big red flag.
> Taken from [Painless Functional Specifications](http://www.joelonsoftware.com/articles/fog0000000036.html)

#### What does into a functional specification. 
First and foremost, the agile process values ['working software over comprehensive documentation'](http://agilemanifesto.org) so your document doesn't need to be exhaustive. It's a roadmap not an encylopedia. Keep is brief, short and to the point. 

A starting point can be found in [this guide](http://www.its-all-design.com/what-actually-goes-in-a-functional-specification/).

This guide is quickly summarised below... 

> 	There are two key elements to a functional specification:
> 	Functions – a description of the interactions between the system and its (human and system) actors
> 	Data – a description of the state of the system


#### Describing functions
> The functions of a system are the interactions that can occur between the system and its actors (through the interfaces). An interaction is a sequence of actor inputs (e.g. a user clicking a mouse button) and system outputs (e.g. displaying some data on the user’s screen). Typically the actor is trying to achieve some objective (log in, search for data, update data, perform a calculation etc.).

#### Describing functions with Use Cases

>I like to use use cases as the main anchor for describing a system’s functions. They are, to my mind, the perfect format for describing interactions between an actor and the system. Laura Brandenberg has a similar love affair with use cases. I’m not going to explain use cases in full (you can click here to read what a use case is), but just in case you’re new to this game, a use case looks something like this:

````
Use Case 1: User Logs On

Main Flow

User launches the application
System prompts user for log-on details (user name and password)
User enters log-on details and submits them
System requests user’s log-on details from the external single-sign on directory
System validates that user’s entered log-on details match those from the directory
System displays the main menu
Alternative Flow 4a: Incorrect log-on details

System tells user their log-on has failed
Return to Main Flow step 2
Alternative Flow 4b: User account locked

System tells user their account is locked and they should call the helpline
Return to Main Flow step 2
````

#### Describing functions with User Stories
An alternative approach to Use Cases is to work with 'User Stories'

> User Stories are a simple way of capturing user requirements throughout a project – an alternative to writing lengthy requirements specifications all up-front. (from [here](http://www.allaboutagile.com/writing-good-user-stories/))

Writing a user story requires you to state:

__As a [user role], I want to [goal], so I can [reason].__

The third part is the most important as it makes the user’s motivation for using the feature explicit. It also:

- (a) gives clarity as to why a feauture is useful;
- (b) can influence how a feature should function;
- (c) can give you ideas for other useful features that support the user’s goals.

Thereby the user story helps to ensure that each requirement is captured at a high level, is feature oriented and covers who, what and why.

User Stories are equivalent to an individual flow or use case but they are much more user oriented. Typically they are organized around the initial statement, include a wireframe, sketch or design that illustrates the feature and its operation, and includes a workflow which specifies the individual steps involved in the process. Take a look at [this example](http://www.allaboutagile.com/user-story-example/)

They're also easy to assemble into a product backlog:  [http://www.mountaingoatsoftware.com/blog/a-sample-format-for-a-spreadsheet-based-product-backlog](http://www.mountaingoatsoftware.com/blog/a-sample-format-for-a-spreadsheet-based-product-backlog). At the start of your project, you're going to prepare an initial list of User Stories up-front. This becomes be the initial Product Backlog that you'll use to estimate and plan what features you can implement in the 7 weeks of this course. 

#### Describing data
Include the following information for data

- Entity name (so that it can be unambiguously referred to)
- Entity description (explaining what the entity actually is – not always obvious)
- Attributes:
   - Name
   - Description (again, not always obvious)
   - Type and allowable values, such as:
      - String, max 50 characters
      - Integer from 0 to 60,000 or blank
      - One of Male, Female or  Not Specified
   - Relationships with other entities:
      - Meaning of relationship (e.g. home address, delivery address)
      - Multiplicity (one-to-one, one-to-many, zero-or-one-to-one etc.)

Note that the above are logical, rather than physical, definitions. For example, a logical type of “Male, Female or Not Specified” might be implemented as a NUMBER where 1=Male, 2=Female, 0=Not Specified, or it might be implemented as a nullable VARCHAR where “M”=Male, “F”=Female and NULL=Not Specified

Not allowed:

- Physical database definitions (table names, column names, column types)
- “Entities” that are actually database tables implementing many-to-many relationships

#### Format, Examples and Templates

The format and approach can vary widely depending on your preferred approach. Some people keep their specs in a Spreadsheet because it's easy to track features, iterations and update as you go. Others prefer web pages or Word documents. It's up to you

Joel on Software provides an [example functional spec](http://www.joelonsoftware.com/articles/WhatTimeIsIt.html) for a fictional website: WhatTimeIsIt.com

You can find templates and examples for it's approach to Functional Specs at: [http://www.its-all-design.com/downloads/](http://www.its-all-design.com/downloads/)

## Bill of Materials

Every hardware project needs a bill of materials. The basics of a bill of materials is a really well organized spreadsheet which contains a detailed list of every part, component, sensor and item that you'll need in order to build your project.

__Your bill of materials should be thorough, should be updated throughout the development process as you make changes and should check components are available and easily shipped with your neeed timeframe.__ You should read this [great guide to bullet proof BoMs](http://www.proto2prod.com/proto2prod/2015/3/11/creating-and-optimizing-a-bill-of-materials-1) by Particle

In your bill of materials, at the very least you should specify:

- Item Type
- Product Code (and/or manufacturer and manufacturer part number)
- Any additional information (like part version number, vendor)
- Quantity of item needed, unit cost and total cost
- A preferred vendor/supplier and a link to part on a vendor page. 

When building your bill of materials you should include all needed items (electronic and otherwise) to reproduce your prototype. Ask the following:

- How are you going to power the device? Does it need a battery pack and what kind of batteries? If it's powered by an outlet is USB sufficient or do you need a [DC power pack / cord](https://www.adafruit.com/products/798) (and perhaps a [barrel jack](https://www.adafruit.com/products/373))
- Do you need a switch to turn power on or off or is your device always on?
- What input devices do you need? Push buttons, momentary switches? 
- How are you provided feedback or creating behavior? Do you need LEDs or RGB LEDs? Are you using audio etc?  What components are most suited to building your desired interactivity and product experience? 
- What sensing is performed and what are the most suitable sensors to gathering the data you need? 
- Don't overlook the simpler components: How many resistors, diodes, transitors will be used in your circuit? 

When you source your components here are some great places to start looking: 

- [Parts.io](http://parts.io) is a great site for discovering all sorts of components to suit your project's needs. 
- For hobbyist components [Adafruit](http://adafruit.com) and [Sparkfun](http://sparkfun.com) are perfect and house a broad a range of components accompanied by detailed tutorials for their use and integration with microcontrollers. They also offer educational discounts on orders. 
- [Digikey](http://www.digikey.com) and [Mouser](http://www.mouser.com/?gclid=CJOzpPfw0ssCFdgGgQod7Y0Ahg) both have a great catalogue of components too. Often at lower prices than the above.
- For non-hardware components like bearings, mounts, threaded rods, washers, magnets, tubing, etc. [McMaster Carr](http://www.mcmaster.com) is a fantastic place to look. 
- [Octopart](https://octopart.com). Want to search all the sites? Octopart is a great tool if you're trying to gut check average price among many distributors and identify common MOQs. It also has a nice [BoM manager tool](https://octopart.com/bom-lookup/manage)!

__Handy Hint__ If you design your circuit with [Fritzing](http://fritzing.org) it will give you the option to automatically [export your bill of materials](http://fab.fritzing.org/how-to/post-fab) at the click of a button. Many CAD tools also allow you to export them too. 


## Learn More

- http://www.allaboutagile.com/user-stories/
- http://www.allaboutagile.com/user-story-example/
- http://www.allaboutagile.com/writing-good-user-stories/
- http://www.its-all-design.com/an-agile-functional-specification/  and http://www.its-all-design.com/what-actually-goes-in-a-functional-specification/
- http://www.joelonsoftware.com/articles/WhatTimeIsIt.html
- http://www.joelonsoftware.com/articles/fog0000000036.html
- http://www.bridging-the-gap.com/functional-specification/
- http://www.mountaingoatsoftware.com/blog/a-sample-format-for-a-spreadsheet-based-product-backlog
