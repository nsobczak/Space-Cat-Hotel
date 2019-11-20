# README

**Goal**: attract as much tourists as possible down to earth.

- you are a space cat
- you run an interplanetary hotel company
- you must recruit space cat employees (worker: harvester or engineer)
- harvester can gather resources
- engineers can construct building that can answer extraterrestrial needs of clients
- when clients arrive you must move them to their room: assign a room and they move to it if it answers its needs and if it's empty, otherwise client keeps on waiting, and leaving if it's too long.
- if client are satisfied with your company they might come down to earth

## Resources

Type:
- oxygen
- raw materials

They are gathered to Earth by harvesters.

## Actors

- Earth => produces workers
- Facility hotel => produces rooms
- Resources => are unlimited
- Facility mine (color and shape) => harvesters gather resources in the mine
- Harvester worker => can harvest resources (go back an forth from resource to mine, resources are unlimited)
- Engineer worker => must gather resources on target planet and build hotel (worker then work at the hotel, can't be used anymore)
- Goal => Animal, time (visual like a color in overcooked), amount of resources needed
- Goal queue => list of goals and time when they appear, remove goal if time expired

## Game logic

### Setup
Game should start with 1 mine on earth and a given number of Harvester worker working there.
Fixed by the level:
- Time limit
- Number max of harvester workers
- Number max of engineer workers
- Goal queue

### Update

- Check game over = when timeleft == 0
- Check if goal is completed == client satisfied
- Update Resources amount
- Check character's actions
