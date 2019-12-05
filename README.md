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
- If client are satisfied with your company they might come down to Earth, your mother planet.

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
Game starts with 1 mine and a given number of Harvester worker working there.
Fixed by the level:
- Time limit
- Number max of harvester workers
- Number max of engineer workers
- Goal queue

### Update

- Check game over = when (timeleft == 0)
- Check if goal is completed => client satisfied
- Update resources amount
- Check character's actions

## Ideas

- limit hotel room max capacity
- engineer should take time building hotel and room in the same way that harvesters need time to harvest mine
- mine should be limited to 1 harvester
- do a tutorial
- option menu should have: sound level + camera movement speed + graphics?
- client appears at some point in the galaxy and player have to select it and click on hotel to assign a room to it, can't click on it if goal is missed, client just goes out and disappears.
- outline actors when mouse is over selectable or facility emplacement (change outline color depending on what we hit?)
- add temp texture/decal to right click location when moving
- add stars appreciation on result screen depending on result
- improve pathfinding
- make facilities rotate with planets
- make selected actor under turning square be a circle
- make facility spawned with red transluscent material => delete it if we right click, fix position and change material to original when we left click on a possible position


### levels
- number: 20
- they should give new gameplay
- worm hole
- moving planets (translating)
- spaceships/satellite/planets crossing

### goal queue
- minimum and max number of goals active at the same time, 2 and 5 for instance
- a timer is used to make a new goal appear, every 10 seconds for instance
- timer is reset when a goal is completed or when a new goal appear
- goal automatically appear if active goal count < min
- timer is paused if active goal count >= max

### Logos
- oxygen
- raw materials
- engineer
- harvester
- earth
- hotel
- mine
