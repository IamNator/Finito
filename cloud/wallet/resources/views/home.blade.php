@extends('layouts.main')
@section('title')
    Wallet
@endsection
@section('content')

    <!--Dashboard top-->
    <section class="section-padding-sm-2 blue-bg">
        <div class="container">
            <div class="row">
                <div class="col-xl-4 col-lg-4 col-md-6 col-sm-6 mb-20">
                    <div class="card">
                        <div class="card-header">
                             Profile <a href="#"><i class="ti-arrow-top-right"></i></a>
                        </div>
                        <div class="card-body">
                        <p>Good Morning! <strong>{{ Auth::user()->name }}</strong></p>
                        <p>You joined In: <strong>{{ Auth::user()->created_at }}</strong></p>
                        </div>
                    </div>
                </div>
                <div class="col-xl-4 col-lg-4 col-md-6 col-sm-6 mb-20">
                    <div class="card">
                        <div class="card-header">
                            Balance
                        </div>
                        <div class="card-body">
                            <p>US Doller: <strong>${{ Auth::user()->wallet*380 }}</strong></p>
                            <p>NG Niara: <strong>NGN{{ Auth::user()->wallet }}</strong></p>
                        </div>
                    </div>
                </div>
                <div class="col-xl-4 col-lg-4 col-md-6 col-sm-6 mb-20">
                    <div class="card">
                        <div class="card-header">
                            Bank Details
                        </div>
                        <div class="card-body">
                        <p>Name: <strong>{{ Auth::user()->name }}</strong></p>
                            <p>Number: <strong>{{ Auth::user()->number }}</strong></p>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </section><!--Dashboard top-->


    <!--Dashboard Bottom-->
    <section class="section-padding-sm-2 blue-bg-2">
        <div class="container">
            @if (session('success'))
    <div class="alert alert-success  alert-dismissible fade show" id="alert" role="alert">
        <button type="button" id="close" class="close" data-dismiss="alert">x</button>
        <li>
            {{ session('success') }}
        </li>
    </div>
@endif

@if (session('failure'))
    <div class="alert alert-danger alert-dismissible fade show" id="alert" role="alert">
        <button type="button" id="close" class="close" data-dismiss="alert">x</button>
       <li>
           {{ session('failure') }}
       </li>
    </div>
@endif

            <div class="row justify-content-center">
                <div class="col-xl-3 col-lg-3 col-md-6 col-sm-6 mb-20">
                    <div class="card mb-30">
                        <div class="card-header">
                            Someone to pay?
                        </div>
                        <div class="card-body">
                            <p>Send money straight to another user or bank</p>
                            <a data-toggle="modal" data-target="#ModalCenter1" class="bttn-small btn-fill"><i class="ti-user"></i> Make a payment</a>
                        </div>
                    </div>
                    <div class="card">
                        <div class="card-header">
                            Receive a payment?
                        </div>
                        <div class="card-body">
                            <p>Fund your account instantly straight from any bank/card.</p>
                            <a data-toggle="modal" data-target="#ModalCenter2" class="bttn-small btn-fill"><i class="ti-direction"></i> Receive payment</a>
                        </div>
                    </div>
                </div>
                <div class="col-xl-9 col-lg-9 col-md-12 mb-20">
                    <div class="transaction-list table-responsive">
                        <table class="table table-hover">
                            <thead>
                              <tr>
                                <th scope="col">Date</th>
                                <th scope="col">Description</th>
                                <th scope="col">Amount</th>
                                <th scope="col">Method</th>
                              </tr>
                            </thead>
                            <tbody>
                                @forelse ($user['transactions'] as $trans )
                            <tr>
                                    <td><span>{{ $trans->created_at }}</span></td>
                                    <td><span>{{ $trans->description }}</span> - {{ $trans->type }}</td>
                                    <td><span>NGN{{ $trans->amount }}</span></td>
                                    <td><span>{{ $trans->method }}</span></td>
                            </tr>
                            @empty
                            <tr>No Data Found</tr>
                            @endforelse

                            </tbody>
                        </table>
                        <!-- Transaction Details Modal -->
                        <div class="modal fade" id="ModalCenter1" tabindex="-1" role="dialog" aria-labelledby="ModalCenter1Title" aria-hidden="true">
                            <div class="modal-dialog modal-lg modal-dialog-centered" role="document">
                                <div class="modal-content">
                                    <div class="row no-gutters">
                                        <div class="col-sm-5 d-flex justify-content-center blue-bg-2 py-4">
                                            <div class="transaction-modal-left my-auto centered">
                                                <div class="mb-30"><i class="flaticon-006-wallet"></i></div>
                                                <h3 class="my-3">Current Balance</h3>
                                                <h4 class="cl-white my-4">NGN{{ Auth::user()->wallet }}</h4>
                                            </div>
                                        </div>
                                        <div class="col-sm-7">
                                            <div class="modal-header">
                                                <h5 class="modal-title" id="ModalCenter1Title">Send Funds</h5>
                                                <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                                                    <span aria-hidden="true">&times;</span>
                                                </button>
                                            </div>
                                            <div class="transaction-modal-details">
                                                <div class="faq-contents">
                                                    <form action="{{ route('send') }}" method="post">
                                                        @csrf
                                                        <div class="form-group">
                                                            <input placeholder="Enter Amount" type="text" name="amount" id="amount" class="form-control">
                                                            <br>
                                                            <input placeholder="Enter Account Number" type="text" name="number" id="number" class="form-control">
                                                        </div>
                                                        <button class="btn btn-success" type="submit">Continue</button>
                                                    </form>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div><!-- /Transaction Details Modal -->
                        </div>

                        <!-- Transaction Details Modal -->
                        <div class="modal fade" id="ModalCenter2" tabindex="-1" role="dialog" aria-labelledby="ModalCenter2Title" aria-hidden="true">
                            <div class="modal-dialog modal-lg modal-dialog-centered" role="document">
                                <div class="modal-content">
                                    <div class="row no-gutters">
                                        <div class="col-sm-5 d-flex justify-content-center blue-bg-2 py-4">
                                            <div class="transaction-modal-left my-auto centered">
                                                <div class="mb-30"><i class="flaticon-006-wallet"></i></div>
                                                <h3 class="my-3">Account Number</h3>
                                            <h4 class="cl-white my-4">{{ Auth::user()->number }}</h4>
                                            </div>
                                        </div>
                                        <div class="col-sm-7">
                                            <div class="modal-header">
                                                <h5 class="modal-title" id="ModalCenter2Title">Fund Account</h5>
                                                <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                                                    <span aria-hidden="true">&times;</span>
                                                </button>
                                            </div>
                                            <div class="transaction-modal-details">
                                                <div class="faq-contents">
                                                    <form action="{{ route('pay') }}" method="post">
                                                        @csrf

                                                        @php
                                                          // Available alpha caracters
                                                         $characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';

                                                        // generate a pin based on 2 * 7 digits + a random character
                                                                $pin = mt_rand(10, 99)
                                                                    . mt_rand(10, 99);
                                                        // shuffle the result
                                                                $number = str_shuffle($pin)
                                                                . $characters[rand(0, strlen($characters) - 1)];
                                                        @endphp
                                                    <input type="hidden" name="email" value="{{ Auth::user()->email }}"> {{-- required --}}
                                                    <input type="hidden" name="orderID" value="{{ $number }}">
                                                        <input type="hidden" name="quantity" value="1">
                                                        <input type="hidden" name="currency" value="NGN">
                                                        <input type="hidden" name="metadata" value="{{ json_encode($array = ['user_id' => Auth::user()->id, 'description' => 'Wallet funding from dashboard', 'type' => 'Deposit']) }}" > {{-- For other necessary things you want to add to your payload. it is optional though --}}
                                                        <input type="hidden" name="reference" value="{{ Paystack::genTranxRef() }}"> {{-- required --}}
                                                        <input type="hidden" name="_token" value="{{ csrf_token() }}"> {{-- employ this in place of csrf_field only in laravel 5.0 --}}
                                                        <div class="form-group">
                                                            <input placeholder="Enter amount in naira" type="text" name="amount" id="amount" class="form-control">
                                                        </div>
                                                        <button class="btn btn-success" type="submit">Fund</button>
                                                    </form>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div><!-- /Transaction Details Modal -->
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </section><!--Dashboard Bottom-->


@endsection
