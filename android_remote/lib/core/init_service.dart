import 'package:android_remote/core/mqtt_adapter.dart';

class InitService {
  static init() {
    MqttAdapter().connect(
      '47.241.6.200',
      1883,
      username: 'rama',
      password: 'rama',
    );
  }
}
