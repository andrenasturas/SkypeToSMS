# SkypeToSMS

Some kind of hack to keep in contact two persons, one being only able to use SMS and the other Skype.

This is a an old project done in 2014. It is very ugly designed, full with hardcoded values, limited and **obsolete**. Published for memories only, not for use.

# Requieremnts

- A server with an X environement.
- Skype installed on Linux with dedicated account.
- Dedicated mobile phone that can be used with gammu to send and recieve SMS.
- [gammu](https://fr.wammu.eu/gammu/)
- [xdotool](https://github.com/jordansissel/xdotool)

## How it used to work

### Skype -> SMS

1. User A send messages to a dedicated Skype bridge account.
2. Messages are recieved by the Skype client on the server running the project.
3. Messages are read from Skype internal database
4. Messages are sent by [gammu](https://fr.wammu.eu/gammu/) to user B's phone number by SMS.

### SMS -> to Skype

1. User B send SMS to a dedicated phone number.
2. Messages are recieved by the phone connected to the server running the project.
3. Messages are read by [gammu](https://fr.wammu.eu/gammu/).
4. Messages are typed with a scripted virtual keyboard ([xdotool](https://github.com/jordansissel/xdotool)) on an actual Skype graphical window, already set on the conversation with User A, and are sent.

## Note

Variables like user A's skype account and user B's phone number, for example, were hard-coded in the code. All of them have been replaced by tokens begining with `VAR_` that should be replaced, or - better - parametrized.

## Licence

Unlicense.