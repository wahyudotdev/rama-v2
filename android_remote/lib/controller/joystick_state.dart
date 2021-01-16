import 'dart:async';

import 'package:android_remote/core/mqtt_adapter.dart';
import 'package:get/get.dart';

enum Pad { A, B, C, D }

class JoystickState extends GetxController {
  int direction = 0;
  int pad = 0;
  double right = 0;
  updateDirection(double deg) {
    if (deg < 45 || deg > 315) this.direction = 1;
    if (deg > 45 && deg < 135) this.direction = 2;
    if (deg > 135 && deg < 225) this.direction = 3;
    if (deg > 225 && deg < 315) this.direction = 4;
    if (deg == 0.0) this.direction = 0;
  }

  leftJoystick(double deg, double th) {
    if (right == 0.0) {
      if (deg < 180 && th > 0.5) this.direction = 2;
      if (deg >= 180 && th > 0.5) this.direction = 4;
      if (deg == 0.0) this.direction = 0;
    }
  }

  rightJoystick(double deg, double th) {
    if ((deg < 90 || deg > 270) && th > 0.5) this.direction = 1;
    if ((deg >= 90 && deg <= 270) && th > 0.5) this.direction = 3;
    if (deg == 0.0) this.direction = 0;
    this.right = deg;
  }

  void onReady() {
    super.onReady();
    Timer.periodic(
        Duration(milliseconds: 500),
        (_) => MqttAdapter()
            .publishMessage('{"dir":${this.direction},"cam":100}'));
    // Timer.periodic(Duration(milliseconds: 500), (_) => print(this.direction));
  }
}
