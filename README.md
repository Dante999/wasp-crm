# WaspCRM

this very simple CRM targets people who want to have their data kept local and
easy accessible via the filesystem without any thirdparty tool.

## Philosophy
The philosophy of WaspCRM is to organize it's data in a folder and file
structure, which can also be explored just with a filebrowser and a texteditor.
So its more like a helping hand for you to organize your files but also with
some analytic and comfort features. You could even think about using a
versioning system like git to commit changes and or do rollbacks if you delete
anything accidentally.

Another good thing about the folder and files approach is, even if you say after
some time you no longer want to use his CRM, you don't have to worry about how
you get your data out of a database or even from any cloud service. Your data is
already there!

Of course, this approach comes with some downsides. Storing data on the local
filesystem isn't as fast as data stored in a database when it comes to complex
queries and search criterias. Also concurrent access and corrupted data is
automatically and well handled by a database. So users which have a very large
amount of customers, articles and invoices and need simultaneously access are
probably wrong here.

## TODOs
- Dropdown list to select a vendor of an article
- Banner with Wasp CRM logo and name on the main panel
- Fix multiline input field
- Fix layout which doesn't resize very well
- base64 encoded and stored images of articles
- Shortcuts like CTRL+S for saving
- Multiline Notes field for Articles
- Convert selector table to multiple columns like one for name, one for id etc.
