'use strict';

// Declare app level module which depends on filters, and services
angular.module('pic32kit', [
    'ngRoute',
    'pic32kit.filters',
    'pic32kit.services',
    'pic32kit.directives',
    'pic32kit.controllers'
])
    .run(function($rootScope) {
        document.addEventListener("starterkit", function(ev) {
            var json = ev['json'];
            //console.log('app document msg event: ' + JSON.stringify(json));
            $rootScope.$broadcast('starterkit', json);
        }, false);
    })
    .config(['$routeProvider', function($routeProvider) {
            $routeProvider.when('/main', {templateUrl: 'partials/main.html', controller: 'MainCtrl'});
            $routeProvider.when('/test', {templateUrl: 'partials/test.html', controller: 'TestCtrl'});
            $routeProvider.otherwise({redirectTo: '/main'});
    }]);
