# Junction Tables in SQL

## What is a junction table?

A junction table (also called a bridge table, join table, linking table, or associative entity) is a table that exists to resolve a many-to-many relationship between two other tables.

Here's the underlying limitation that makes them necessary: a foreign key column can only hold one value per row. That naturally expresses "many rows point to one row" — a one-to-many relationship. It cannot express "many rows on both sides point to many rows on the other side."

A junction table solves this by splitting one many-to-many relationship into two ordinary one-to-many relationships:

```
User ---- 1:N ----> Likes <---- N:1 ---- Post
```

Each row in Likes is one instance of "this user liked this post." User relates to Likes as 1:N, and Post relates to Likes as 1:N. Put those together and you get User-to-Post as many-to-many, without any column ever needing to hold more than one value.

---

## The simplest test

A table is a junction table if every single row in it just reads as a relationship — "this connects to that" — and nothing more.

If you can read a row out loud and it sounds like a full sentence describing a thing ("this message was sent by this person to that person at this time"), it's a real entity, not a junction table.

If you can read a row out loud and it only sounds like a connection ("this user, this post" or "this follower, this person they follow"), with nothing else being described, it's a junction table.

A second way to check the same idea: ask whether one row of table A can relate to many rows of table B, while at the same time one row of B can relate to many rows of A. If yes, that's a many-to-many relationship, and you need a junction table to hold it.

---

## Anatomy of a junction table

A junction table usually has:

- Two foreign key columns, one pointing to each parent table
- A composite primary key made from those two foreign keys together, which stops the same relationship from being recorded twice
- Optionally, a few extra columns describing the relationship itself, such as a timestamp for when it was created

---

## Applying this to your Instagram schema

**Likes** connects User and Post. One user can like many posts, and one post can be liked by many users. Every row just says "this user liked this post." Junction table.

**Follow** connects User and User. One user can follow many users, and one user can be followed by many users. Every row just says "this user follows that user." Junction table.

**PostHashtag** connects Post and Hashtag. One post can carry many hashtags, and one hashtag can appear on many posts. Every row just says "this post has this hashtag." Junction table.

**Message** also connects User and User, using two foreign keys just like Follow does. But read a row out loud: "this message, sent by this user, to that user, at this time." That's describing a thing that happened, not just a bare connection. Message has its own identity through message_id, and sent_at describes an attribute of that specific message. Not a junction table.

**Comment** connects User and Post. But again, read a row out loud: "this comment, with this text, written by this user, on this post." That's a thing with its own content, not a bare connection. Not a junction table.

The pattern to notice: Message and Follow both reference User twice, and Comment and Likes both reference Post. Referencing the same table twice, or referencing two different tables, doesn't decide the question. What decides it is whether the row is only recording a connection, or whether it's describing something with its own identity and attributes.

---

## More practice questions

**1. Why does Likes use a composite primary key (user_id, post_id) instead of its own auto-increment like_id?**

Either design can work, but the composite key has a built-in advantage: it makes it structurally impossible for the same user to like the same post twice, because the primary key constraint itself blocks the duplicate row. With a separate like_id, you would need an extra unique constraint on (user_id, post_id) to get the same guarantee.

**2. Why can't hashtags just be stored as a comma-separated string inside Post.content, instead of using PostHashtag?**

A single column holding something like "travel,fun" is not queryable in any clean way. You could not efficiently find all posts tagged #travel without parsing the string with something like a LIKE match, which does not use an index well, cannot confirm the hashtag actually exists as a real entity, and can produce false matches such as #fun matching #funny. A column cannot cleanly hold a list of related things, which is exactly the problem junction tables are built to solve.

**3. If a user should be able to like the same post more than once, with a separate timestamp for each like, how would Likes need to change?**

The composite primary key (user_id, post_id) would have to be removed, since it currently limits the table to one row per user-post pair. You would add a surrogate key such as like_id and a liked_at timestamp, so each like becomes its own event instead of a single toggled state.

**4. Follow has no columns besides its two foreign keys. Is a table allowed to have only foreign keys and nothing else?**

Yes. This is actually the cleanest form a junction table can take. Its whole purpose is to record that a relationship exists, so it does not need anything beyond identifying which two rows are connected. Adding a followed_at timestamp later is optional extra detail, not a requirement.

**5. Why does Follow reference User twice, with follower_id and following_id, instead of needing two separate tables?**

Because a follower and someone being followed are the same kind of thing: both are just users. There is no need for two different tables when one table can be referenced by two differently named foreign key columns. This is called a self-referencing relationship, and it is a normal, valid pattern.

**6. What would go wrong if PostHashtag used hashtag_id alone as its primary key, instead of the pair (post_id, hashtag_id)?**

hashtag_id alone is not unique in that table, because the same hashtag legitimately appears on many different posts, so it needs to repeat across rows. A primary key on hashtag_id alone would make it impossible to tag more than one post with the same hashtag, since primary keys must be unique.

**7. Is Comment a junction table, since it references both User and Post?**

No. Comment has its own identity through comment_id and its own attribute through text, neither of which belongs to a junction. It is a full entity that happens to reference a user and a post to record who wrote it and where, in the same way Message references two users to record who sent it and who received it.

---

## Summary

A junction table exists only to let two tables relate many-to-many, by splitting that relationship into two ordinary one-to-many links. Every row in it reads as a connection and nothing more. If a table's rows read as something with their own identity and attributes, like Message or Comment, it is a real entity that happens to reference other tables, not a junction table, even if it has two foreign keys.