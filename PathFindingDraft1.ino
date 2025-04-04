#include <math.h>;

/*class Boat{
      public:
           String GetCurrentBearing() {
                 return CurrentBearing;
           }

           void SetCurrentBearing(String NewBearing) {
                  Bearing = NewBearing;
           }
           float GetLong(){
              return LongCoordinate;
           }
           float GetLat(){
              return LatCoordinate;
           }
           void UpdateLong(float NewLong){
              LongCoordinate = NewLong;
           }
           void UpdateLat(float NewLat){
              LatCoordinate = NewLat;
           }
      private:
        float CurrentLongCoordinate = 0;
        float CurrentLatCoordinate = 0;
        float CurrentBearing = 0;
}; */
float TargetLong = 57;
float TargetLat = 20;
float CurrentLong = 30;
float CurrentLat = 40;
float CurrentBearing = 0;
// for triganometry, Longitute is always the opposite, latitude is always the adjacent.
//for turning, will always be turning left from current bearing to desired bearing. 
//required turn angle will tell you how far left you must turn in degrees.
void FindPath(float TargetLong, float TargetLat, float CurrentLong, float CurrentLat){
  float LongDifference = (TargetLong - CurrentLong);
  float LatDifference = (TargetLat - CurrentLat);
  float RequiredDistance = sqrt(sq(LongDifference)+sq(LatDifference));
  float AngleFromNorth = atan(LongDifference/LatDifference) * (180/M_PI);
  if(LatDifference < 0){
    AngleFromNorth = AngleFromNorth + 180;
  }
  float RequiredTurnAngle = CurrentBearing - AngleFromNorth;
  Serial.println((String) "Required Distance:" + RequiredDistance + "   AngleFromNorth:" + AngleFromNorth + "   Long Diff:" + LongDifference + "   Lat Diff:" + LatDifference);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  FindPath(27,-53,0,0);

}
