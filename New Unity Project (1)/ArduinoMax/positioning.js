"use strict";

var ss = { x:250, y: 500};
var head = {x:500, y:250, angle:270 };
var rightEar = {x:0,y:0,angle:0};
var leftEar = {x:0, y:0,angle:0};

var angleToLeft =0;
var angleToRight =0;

var angleToHead =0;



function list()
{
	var a = arrayfromargs(arguments);
	//post("received list " + a + "\n");

  head.x = a[0];
  head.y = a[1];
  ss.x = a[2];
  ss.y = a[3];
  head.angle = a[4];



  var opp = head.x-ss.x;
  var adj = head.y-ss.y;
  var hyp = Math.sqrt( Math.pow(opp,2) + Math.pow(adj,2) );

  angleToHead =  + ( Math.acos( adj/hyp ) );

  leftEar.angle = head.angle-Math.PI/2;
  rightEar.angle = head.angle+Math.PI/2;

  var angles = [
left: trueAngle(leftEar),
right: trueAngle(rightEar)
];

  outlet(0,"myvalue","is",angles);

}

function trueAngle(ear){
  var result = (ear.angle-angleToHead+Math.PI/2)%360;
  if(result>Math.PI) result = Math.PI*2-result;
  else if(result<-Math.PI) result = result+Math.PI*2;
  return result;
}

