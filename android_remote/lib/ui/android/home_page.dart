import 'package:android_remote/core/init_service.dart';
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
    InitService.init();
    Pixel().init(context);
    return Container(
      child: SafeArea(
        child: GetBuilder<MqttState>(
          init: MqttState(),
          builder: (snapshot) {
            return Scaffold(
              body: Container(
                child: Row(
                  children: [
                    Container(
                      padding: EdgeInsets.all(Pixel.x * 10),
                      child: JoystickView(
                        backgroundColor: Colors.blue,
                        innerCircleColor: Colors.orange,
                        onDirectionChanged: (deg, th) =>
                            print('deg: $deg   th:$th'),
                      ),
                    ),
                    Container(
                      padding: EdgeInsets.all(Pixel.x * 10),
                      child: PadButtonsView(
                        backgroundPadButtonsColor: Colors.orange,
                        padButtonPressedCallback: (i, gesture) => print('$i'),
                      ),
                    ),
                  ],
                ),
              ),
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
