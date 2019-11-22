# README

**Goal**: You are a space cat who runs an interplanetary hotel company and wants to attract as many tourists as possible down to earth.

**How to** build and manage:
- You must recruit fellow space cat employees (worker are either harvester or engineer)
- Harvester can gather resources (oxygen and raw materials)
- Engineers can construct facilities and work in hotels
- Facilities are either mine to collect resources or hotel to answer clients' needs
- Clients needs are displayed at the left hand corner. You must prepare the correct hotel with the right number of free rooms that are managed by the correct number of engineers.
- An engineer can manage 2 room. So if a client needs 3 rooms, it will need at least 2 engineers in the hotel.
- If there are already 2 engineers in the hotel, 3 rooms occupied and 1 free room, you need to construct 2 more rooms and recruit 1 extra engineer in that hotel.
- If client keeps on waiting for too long it will leave.
- if client are satisfied with your company they might come down to Earth, your mother planet.

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
