// To parse this JSON data, do
//
//     final robot = robotFromMap(jsonString);

import 'dart:convert';

class Robot {
  Robot({
    this.x,
    this.y,
    this.z,
  });

  int x;
  int y;
  int z;

  factory Robot.fromJson(String str) => Robot.fromMap(json.decode(str));

  String toJson() => json.encode(toMap());

  factory Robot.fromMap(Map<String, dynamic> json) => Robot(
        x: json["x"],
        y: json["y"],
        z: json["z"],
      );

  Map<String, dynamic> toMap() => {
        "x": x,
        "y": y,
        "z": z,
      };
}
