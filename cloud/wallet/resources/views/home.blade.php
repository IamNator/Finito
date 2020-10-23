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
                            <tr>
                                @forelse ($user->transactions as $trans )
                                    <td><span>{{ $trans->created_at }}</span></td>
                                    <td><span>{{ $trans->description }}</span> - {{ $trans->type }}</td>
                                    <td><span>{{ $trans->amount }}</span></td>
                                    <td><span>{{ $trans->method }}</span></td>
                                    @empty
                                    <td>No Data Found</td>
                                @endforelse
                            </tr>
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
                                                <h3 class="my-3">Padlock Holdings Bank Corp</h3>
                                                <h4 class="cl-white my-4">$598.20</h4>
                                                <p class="cl-white">10 Feb 2020</p>
                                                <div class="completed">Completed</div>
                                            </div>
                                        </div>
                                        <div class="col-sm-7">
                                            <div class="modal-header">
                                                <h5 class="modal-title" id="ModalCenter1Title">Transaction Details</h5>
                                                <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                                                    <span aria-hidden="true">&times;</span>
                                                </button>
                                            </div>
                                            <div class="transaction-modal-details">
                                                <div class="faq-contents">
                                                    <ul class="accordion">
                                                        <li>
                                                            <a href="#">Transaction details</a>
                                                            <p>
                                                                <strong>Transaction ID</strong> <br><span>35791598</span><br><br>
                                                                <strong>To</strong> <br><span>Namecheap Ltd.</span><br><br>
                                                                <strong>Description</strong> <br><span>Domain Purchasing cost felis id rhoncus eros dui</span>
                                                            </p>
                                                        </li>
                                                        <li>
                                                            <a href="#">Transfer details</a>
                                                            <p>
                                                                <strong>Transfer ID</strong> <br><span>587935791598</span><br><br>
                                                                <strong>Transfer amount</strong> <br><span>5,326.36 USD</span><br><br>
                                                                <strong>Exchange rate</strong> <br><span>1 USD = 0.92 GBP</span>
                                                            </p>
                                                        </li>
                                                        <li>
                                                            <a href="#">Transaction history</a>
                                                            <p>
                                                                <strong>Completed</strong> <br><span>15 Feb 2020</span><br><br>
                                                                <strong>Approved</strong> <br><span>15 Feb 2020</span><br><br>
                                                                <strong>Under review</strong> <br><span>15 Feb 2020</span>
                                                            </p>
                                                        </li>
                                                    </ul>
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
                                                <h3 class="my-3">Padlock Holdings Bank Corp</h3>
                                                <h4 class="cl-white my-4">$598.20</h4>
                                                <p class="cl-white">10 Feb 2020</p>
                                                <div class="completed">Completed</div>
                                            </div>
                                        </div>
                                        <div class="col-sm-7">
                                            <div class="modal-header">
                                                <h5 class="modal-title" id="ModalCenter2Title">Transaction Details</h5>
                                                <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                                                    <span aria-hidden="true">&times;</span>
                                                </button>
                                            </div>
                                            <div class="transaction-modal-details">
                                                <div class="faq-contents">
                                                    <ul class="accordion">
                                                        <li>
                                                            <a href="#">Transaction details</a>
                                                            <p>
                                                                <strong>Transaction ID</strong> <br><span>35791598</span><br><br>
                                                                <strong>To</strong> <br><span>Namecheap Ltd.</span><br><br>
                                                                <strong>Description</strong> <br><span>Domain Purchasing cost felis id rhoncus eros dui</span>
                                                            </p>
                                                        </li>
                                                        <li>
                                                            <a href="#">Transfer details</a>
                                                            <p>
                                                                <strong>Transfer ID</strong> <br><span>587935791598</span><br><br>
                                                                <strong>Transfer amount</strong> <br><span>5,326.36 USD</span><br><br>
                                                                <strong>Exchange rate</strong> <br><span>1 USD = 0.92 GBP</span>
                                                            </p>
                                                        </li>
                                                        <li>
                                                            <a href="#">Transaction history</a>
                                                            <p>
                                                                <strong>Completed</strong> <br><span>15 Feb 2020</span><br><br>
                                                                <strong>Approved</strong> <br><span>15 Feb 2020</span><br><br>
                                                                <strong>Under review</strong> <br><span>15 Feb 2020</span>
                                                            </p>
                                                        </li>
                                                    </ul>
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
