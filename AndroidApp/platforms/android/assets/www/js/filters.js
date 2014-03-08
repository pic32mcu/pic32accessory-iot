'use strict';

/* Filters */

angular.module('pic32kit.filters', [])
    .filter('toCelsius', function($filter) {
        var stdNumberFilter = $filter('number');
        return function(value) {
            return (value? stdNumberFilter(value - 273.15, 1) : 'undefine');
        };
    })
    .filter('interpolate', ['version', function(version) {
        return function(text) {
            return String(text).replace(/\%VERSION\%/mg, version);
        };
    }]);
