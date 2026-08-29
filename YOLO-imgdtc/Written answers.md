Q.Two cameras mounted on a car both see the same person. One reports
  the person is 8 metres away, the other reports 11 metres. There is no
  human available to say which is correct. Write down a rule for what the
  car should believe. Any rule is acceptable provided you justify it

A. The difference in the readings is 3m at the readings of 8m and 11m, that is about 35-40% error which is too significant to just ignore as noise , it could indicate that
there is something faulty in the sensor readings. We can define a rule1 which determines if the error is too significant to ignore:
    rule1: for 10m of distance 1m of error can be regarded as noise and this limit scales with the square of distance multiplier,
           that is for 20m , 4m of error is acceptable, for 30m 9m of error is acceptable and so on
           therefore for n metre of distance, (n/10)^2 m error is acceptable.
    if the error exceeds this limit, we proceed with rule2 and rule3 (which is our case in this question),
    rule2: we can try to rule out the faulty reading using the speed of camera,
           we know the speed of camera, hence we can calculate how much does the distance reading to the person has to decrease by in the next x seconds,
           (where x is in milliseconds). Therefore we can check in which camera the reading decreases by the right amount given the speed of the car and
           time elapsed, we can rule out the faulty sensor.
    rule3(heuristic): if it comes to braking on detecting a person,
                      we can more generally prefer the lesser reading over the greater reading.
                      Since it is better to brake early at the cost of passenger comfort and stopping earlier than needed,
                      than braking late and hitting the person.


Q. Your model runs at 4 frames per second. The car travels at 15 metres per
   second. How far does the car move between two consecutive detections?
   What does this imply about using this model on a real vehicle, and what
   would you sacrifice in order to fix it?

A. Since the model runs at 4fps and car moves 15m in 1 second, 
   1frame is detected at 1/4s and hence the car moves 15/4m = 3.75m during two consecutive detections.
   This implies that if it is used on a real vehicle, the model lags behind by about 3.75m about the environment around the car,
   compared to where the car really is. In a real world with real closeby fast moving traffic, this could pose actual challenges since
   the objects that the model may have detected have moved to a different position by the time the data is actually processed and acted upon by the car.
   Now what to sacrifice-
   The most obvious and generic answer is speed, since if we move slowly we give the model more time and hence things are more in sync.
   But moving too slowly isn't really feasible hence,
   What we can also do is make the model act on fewer frames, instead of waiting for 4frames , we can act on 2 frames.
   We will have to sacrifice accuracy of our actions on this but we can improve upon that by using technologies like frame generation,
   which instead of acting on actual captured frames, guess where the objects in a certain frame might have moved to and act on that.
