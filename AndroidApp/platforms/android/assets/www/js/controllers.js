'use strict';

/* Controllers */
angular.module('pic32kit.controllers', [])
    .controller('MainCtrl', [
        '$scope', 'Weather', 'Cities', 'Leds', 'Buttons', 'Starterkit', 'ToggleLed',
        function($scope, Weather, Cities, Leds, Buttons, Starterkit, ToggleLed) {

            $scope.leds = Leds.create();

            $scope.buttons = Buttons.create();

            $scope.weather = Weather.create();
            //$scope.weather=new Weather();

            $scope.cities = Cities.create();
            $scope.$watch('cities.getSelected()', function() {
                $scope.weather.setIcon(null);
                $scope.weather.setBrief(null);
                $scope.weather.setDesc(null);
                $scope.weather.setTemperature(null);
                $scope.weather.setTime(null);
                $scope.weather.updateWeather($scope.cities.getSelected().name);
            });
            $scope.weather.updateWeather($scope.cities.getSelected().name);

            var handler = function(json) {
                if (json.event === 'led-status') {
                    console.log('led-status: id=' + json.id + ', status=' + json.status);
                    $scope.leds.updateStatus(parseInt(json.id), json.status);
                } else if (json.event === 'button-status') {
                    console.log('button-status: id=' + json.id + ', status=' + json.status);
                    $scope.buttons.updateStatus(parseInt(json.id), json.status);
                } else if (json.event === 'city-next') {
                    console.log('city-next');
                    $scope.cities.selectNext();
                } else if (json.event === 'city-prev') {
                    console.log('city-prev');
                    $scope.cities.selectPrev();
                } else {
                    console.log('unknown event = ' + json.event);
                }
            };

            $scope.$on('starterkit', function(ev, json) {
                if (json) {
                    //console.log('controller $scope msg event: ' + ', json = ' + JSON.stringify(json));
                    $scope.$apply(handler(json));
                }
            });

            Starterkit.start();
            $scope.ledtask = ToggleLed.create();
            $scope.ledtask.start(3, 1000);
            $scope.$on('$destroy', function() {
                $scope.ledtask.stop();
            });

        }])
    .controller('TestCtrl', [function() {

        }]);