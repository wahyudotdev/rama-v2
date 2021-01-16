import 'package:android_remote/controller/joystick_state.dart';
import 'package:android_remote/core/mqtt_adapter.dart';
import 'package:android_remote/controller/mqtt_state.dart';
import 'package:control_pad/control_pad.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'widget/pixel.dart';

class HomePage extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    Pixel().init(context);
    return Container(
      child: SafeArea(
        child: GetBuilder<MqttState>(
          init: MqttState(),
          builder: (snapshot) {
            return Scaffold(
              body: GetBuilder<JoystickState>(
                  init: JoystickState(),
                  builder: (joystick) {
                    return Container(
                      child: Row(
                        children: [
                          Container(
                            padding: EdgeInsets.all(Pixel.x * 10),
                            child: JoystickView(
                                backgroundColor: Colors.blue,
                                innerCircleColor: Colors.orange,
                                showArrows: true,
                                interval: Duration(milliseconds: 500),
                                onDirectionChanged: (deg, th) =>
                                    joystick.leftJoystick(deg, th)),
                          ),
                          Container(
                            padding: EdgeInsets.all(Pixel.x * 10),
                            child: JoystickView(
                                backgroundColor: Colors.blue,
                                innerCircleColor: Colors.orange,
                                showArrows: true,
                                interval: Duration(milliseconds: 500),
                                onDirectionChanged: (deg, th) =>
                                    joystick.rightJoystick(deg, th)),
                          ),
                        ],
                      ),
                    );
                  }),
              floatingActionButton: FloatingActionButton(
                child: Icon(Icons.cast_connected),
                onPressed: () => MqttAdapter().publishMessage('tes pesan tes'),
              ),
            );
          },
        ),
      ),
    );
  }
}
