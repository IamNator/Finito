<?php

namespace App\Http\Controllers;


use Illuminate\Http\Request;
use Illuminate\Support\Facades\Redirect;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\DB;
use App\Http\Requests;
use App\Http\Controllers\Controller;
use Paystack;
use App\Models\Transaction;
use App\Models\User;



class PaymentController extends Controller
{
    public function redirectToGateway()
    {
        try{
            return Paystack::getAuthorizationUrl()->redirectNow();
        }catch(\Exception $e) {
            session()->flash('failure','An error occured or the paystack token has expired. Please refresh the page and try again.');
            return Redirect::back();
        }
    }

    public function send(Request $request)
    {
        $number = $request->number;
        $amount = $request->amount;
        $user = DB::table('users')
        ->where('number', $number)->first();
        if($user == '' || $user->number == AUth::user()->number || $amount >= Auth::user()->wallet){
            session()->flash('failure','Please check the transaction, something is wrong');
            $user = User::find(Auth::user()->id);
            return redirect()->route('home', [
                'user' => $user,
            ]);
        }
        return view('transfer', [
            'trans' => $user,
            'amount' => $amount
        ]);
    }

    public function send_submit(Request $request)
    {
        $transaction = new Transaction();
        $transaction->user_id  = Auth::user()->id;
        $transaction->description = $request->description;
        $transaction->amount = $request->amount;
        $transaction->type = 'Transfer';
        $transaction->method = 'Web';
        $transaction->save();

        $wallet = Auth::user()->wallet - $request->amount;


        DB::table('users')
        ->where('id', Auth::user()->id)
        ->update(['wallet' => $wallet]);
        //////
        $transaction = new Transaction();
        $transaction->user_id  = $request->id;
        $transaction->description = $request->description;
        $transaction->amount = $request->amount;
        $transaction->type = 'Deposit';
        $transaction->method = 'Web';
        $transaction->save();

        $wallet = $request->wallet + $request->amount;


        DB::table('users')
        ->where('id', $request->id)
        ->update(['wallet' => $wallet]);
        /////
        session()->flash('success','Funds Sent');

        $user = User::find(Auth::user()->id);

        return redirect()->route('home', [
            'user' => $user,
        ]);
    }

    /**
     * Obtain Paystack payment information
     * @return void
     */
    public function handleGatewayCallback()
    {
        $paymentDetails = Paystack::getPaymentData();

        if($paymentDetails['data']['status'] == 'success'){

            $transaction = new Transaction();
            $transaction->user_id  = $paymentDetails['data']['metadata']['user_id'];
            $transaction->description = $paymentDetails['data']['metadata']['description'];
            $transaction->amount = $paymentDetails['data']['amount'];
            $transaction->type = $paymentDetails['data']['metadata']['type'];
            $transaction->method = 'Card';
            $transaction->save();

            $wallet = Auth::user()->wallet + $paymentDetails['data']['amount'];


            DB::table('users')
            ->where('id', $paymentDetails['data']['metadata']['user_id'])
            ->update(['wallet' => $wallet]);

            session()->flash('success','Funding Successful');

            $user = User::find(Auth::user()->id);

            return redirect()->route('home', [
                'user' => $user,
            ]);

        }

        // Now you have the payment details,
        // you can store the authorization_code in your db to allow for recurrent subscriptions
        // you can then redirect or do whatever you want
    }
}
