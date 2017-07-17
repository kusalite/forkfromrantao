# Submitting work


All student assignments in this course will take the form of [Markdown pages](https://guides.github.com/features/mastering-markdown/) (see this [cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet) too) submitted as [pull requests](https://help.github.com/articles/using-pull-requests/) through Github. Our course repo is: [https://github.com/daraghbyrne/advancediot2016/](https://github.com/daraghbyrne/advancediot2016/). 

Before issuing a pull request, you should make sure your [forked repo is synced](https://help.github.com/articles/syncing-a-fork/) with the upsteam/master repository. This will avoid headaches. See below

For information on using Git and Github, take a [look at the guide](../tutorials/using-git-and-github.md)

Requirements for each of the different assignment types are available below:

Expectations for [Research Exercise](research-exercise.md) assignments.
Expectations for [Tutorial](adding-tutorials.md) assignment.
Expectations for Sprints (below)
Expectations for the Final Documentation (below)

----

## Expectations for Sprints

More detail soon. 

## Expectations for Final Documentation

More detail soon. 

----

## Syncing Upsteam Repo

If you're using the Desktop Client this is unbelievably easy:

- Just click the 'update from' button in your repository's header information: [https://help.github.com/desktop/guides/contributing/syncing-your-branch/](https://help.github.com/desktop/guides/contributing/syncing-your-branch/)
- Then create a pull request: [https://help.github.com/desktop/guides/contributing/sending-a-pull-request/](https://help.github.com/desktop/guides/contributing/sending-a-pull-request/)

If you're not using the desktop client, you'll need to follow these steps to fetch the up-to-date _upstream_ repo

First, read: 

- [https://help.github.com/articles/syncing-a-fork/](https://help.github.com/articles/syncing-a-fork/) and 
- [http://stackoverflow.com/questions/7244321/how-to-update-a-github-forked-repository](http://stackoverflow.com/questions/7244321/how-to-update-a-github-forked-repository) and 
- [https://gun.io/blog/how-to-github-fork-branch-and-pull-request/](https://gun.io/blog/how-to-github-fork-branch-and-pull-request/) - the last one is particularly good


Open up your Terminal window on Mac and navigate to the folder you're using... then 

````
# Add the remote, call it "upstream":
# Note you only need to do this the first time

git remote add upstream https://github.com/whoever/whatever.git

# Fetch all the branches of that remote into remote-tracking branches,
# such as upstream/master:

git fetch upstream

# Make sure that you're on your master branch:

git checkout master

# Rewrite your master branch so that any commits of yours that
# aren't already in upstream/master are replayed on top of that
# other branch:

git rebase upstream/master
````

----