<?php

use Illuminate\Support\Facades\Route;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', function () {
    return view('welcome');
});

Auth::routes();

Route::get('/home', [App\Http\Controllers\HomeController::class, 'index'])->name('home');
Route::post('/pay', [App\Http\Controllers\PaymentController::class, 'redirectToGateway'])->name('pay');
Route::post('/send', [App\Http\Controllers\PaymentController::class, 'send'])->name('send');
Route::post('/send/submit', [App\Http\Controllers\PaymentController::class, 'send_submit'])->name('send.submit');
Route::get('/payment/callback', [App\Http\Controllers\PaymentController::class, 'handleGatewayCallback'])->name('pay.continue');


// Route::post('/pay', [
//     'uses' => 'PaymentController@redirectToGateway',
//     'as' => 'pay'
// ]);
// Route::get('/payment/callback', 'PaymentController@handleGatewayCallback');
