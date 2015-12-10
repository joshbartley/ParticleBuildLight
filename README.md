# ParticleBuildLight
Firmware for the Particle Photon to function as a CI Build Light or application error monitor. Uses the particle cloud to interface with the particle and provide an endpoint to access through tools like AppDynamics or any other system that can send custom HTTP calls.


##Commands

###Circle

Supported colors Green Red Blue Yellow

###Flash

Supported colors Green Red Blue Yellow

##Example - 

Replace with your DEVICE_ID and ACCESS_TOKEN from the particle build system. 

POST https://api.particle.io/v1/devices/{DEVICE_ID}/circle
Content-Type: application/x-www-form-urlencoded
Body:
access_token={ACCESS_TOKEN}&arg=green
