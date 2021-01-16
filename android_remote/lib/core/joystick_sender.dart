import 'package:android_remote/controller/mqtt_state.dart';
import 'package:get/get.dart';

class JoystickSender {
  final adapter = Get.put(MqttState());
}
